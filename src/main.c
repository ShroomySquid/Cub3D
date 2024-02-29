/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/29 13:38:21 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	set_player(t_cube *cube)
{
	uint32_t x;
	uint32_t y;

	x = 0;
	y = 0;
	while (x < cube->player->width)
	{
		while (y < cube->player->height)
		{
			mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 255));
			y++;
		}
		y = 0;
		x++;
	}
}

void	ft_player(void *param)
{
	t_cube *cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
		cube->player->instances[0].y -= 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_UP))
		cube->player->instances[0].y -= 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
		cube->player->instances[0].y += 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN))
		cube->player->instances[0].y += 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
		cube->player->instances[0].x -= 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->player->instances[0].x -= 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
		cube->player->instances[0].x += 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->player->instances[0].x += 2;
}

void	ft_general(void *param)
{
	t_cube *cube;

	cube = param;	
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);		
}

void	set_map(t_cube *cube, int *map)
{
	uint32_t x;
	uint32_t y;
	int i;
	uint32_t max_coord;

	x = 0;
	y = 0;
	i = 0;
	max_coord = 8;
	while (x < max_coord && map[i])
	{
		while (y < max_coord && map[i])
		{
			if (map[i] == 1)
				mlx_image_to_window(cube->mlx, cube->wall_img, (y * 32), (x * 32));
			if (map[i] == 2 || map[i] == 3)
				mlx_image_to_window(cube->mlx, cube->floor_img, (y * 32), (x * 32));
			y += 1;
			i += 1;
		}
		y = 0;
		x += 1;
	}
	//set_player(cube, map);
}

void	force_exit(t_cube *cube, char **map)
{
	if (map)
		free_all(map);
	if (cube)
		free(cube);
	mlx_terminate(cube->mlx);
}

int main(int argc, char **argv)
{
	t_cube	*cube;
	char	**map;

	if (argc != 2)
		return (error_argc());
	cube = ft_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (error_func("ft_calloc"));
	map = render_map(cube, argv);
	if (!map)
		return (free(cube), 1);
	if (check_map(map))
		return (force_exit(cube, map), 1);
	printf("salut Width: %d, Height: %d\n", WIDTH, HEIGHT);
	cube->mlx = mlx_init(WIDTH, HEIGHT, "zzzz", true);
	if (!cube->mlx)
		return (force_exit(cube, map), error_func("mlx_init"));
	printf("salut 1.1\n");
	cube->wall_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->wall_img)
		return (force_exit(cube, map), error_func("mlx_new_image"));
	printf("salut 1.2\n");
	cube->floor_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->floor_img)
		return (force_exit(cube, map), error_func("mlx_new_image"));	
	printf("salut 1.3\n");
	cube->player = mlx_new_image(cube->mlx, 4, 4);
	if (!cube->player)
		return (force_exit(cube, map), error_func("mlx_new_image"));
	printf("salut 1.5\n");
	set_player(cube);
	printf("salut2\n");
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	printf("salut 2.2\n");
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	printf("salut 2.3\n");
	renderloop(cube->mlx, map, cube);
	printf("salut3\n");
	mlx_loop_hook(cube->mlx, ft_general, cube);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop(cube->mlx);
	printf("salut4\n");
	mlx_terminate(cube->mlx);
	return (0);
}
