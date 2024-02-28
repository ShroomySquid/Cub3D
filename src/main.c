/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/28 11:04:00 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int error_msg(char *failed_func)
{
	printf("Function %s failed\n", failed_func);
	return (1);
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_player(void *param)
{
	t_cube	*cube;

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
	t_cube	*cube;

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

int main(int argc, char **argv)
{
	t_cube	*cube;

	(void)argc;
	(void)argv;
	cube = ft_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (error_msg("ft_calloc"));
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cube->mlx)
		return (error_msg("mlx_init"));
	cube->wall_img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->wall_img)
		return (error_msg("mlx_new_image"));		
	cube->floor_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->floor_img)
		return (error_msg("mlx_new_image"));	
	cube->player = mlx_new_image(cube->mlx, 4, 4);
	if (!cube->player)
		return (error_msg("mlx_new_image"));	
	cube->map = open(argv[1], O_RDONLY);
	ft_memset(cube->player->pixels, 255, cube->player->width * cube->player->height * sizeof(int32_t));
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	render_map(cube);
	//mlx_image_to_window(cube->mlx, cube->map, 0, 0);
	//mlx_image_to_window(cube->mlx, cube->random_img, 32, 32);
	mlx_image_to_window(cube->mlx, cube->player, 64, 64);
	mlx_loop_hook(cube->mlx, ft_general, cube);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	return (0);
}
