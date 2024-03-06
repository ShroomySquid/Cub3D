/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/06 11:26:44 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
	if (mlx_is_key_down(cube->mlx, MLX_KEY_E) && cube->rotation++ >= 361)
		cube->rotation = 1;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_Q) && cube->rotation-- <= 0)
		cube->rotation = 361;
}

void	ft_general(void *param)
{
	t_cube	*cube;

	cube = param;	
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
}

void	force_exit(t_cube *cube)
{
	if (cube && cube->map && cube->map->map)
		free_all(cube->map->map);
	if (cube && cube->map)
		free(cube->map);
	if (cube)
		free(cube);
	mlx_terminate(cube->mlx);
}

int main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
		return (error_argc());
	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (error_func("malloc"));
  	cube->rotation = 1;
	cube->map = malloc(sizeof(t_map));
	if (!cube->map)
		return (error_func("malloc"));
	cube->map->map = render_map(cube, argv);
	if (check_map(cube))
		return (force_exit(cube), 1);
	if (!cube->map->map)
		return (force_exit(cube), 1);
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D\n", true);
	if (!cube->mlx)
		return (force_exit(cube), error_func("mlx_init"));
	cube->wall_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->wall_img)
    return (force_exit(cube), error_func("mlx_new_image"));
	cube->render = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->render)
		return (force_exit(cube), error_func("mlx_new_image"));
	cube->floor_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->floor_img)
		return (force_exit(cube), error_func("mlx_new_image"));	
	cube->player = mlx_new_image(cube->mlx, 4, 4);
	if (!cube->player)
		return (force_exit(cube), error_func("mlx_new_image"));
	set_player(cube);
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	mlx_image_to_window(cube->mlx, cube->player, 64, 64);
	renderloop(cube->mlx, cube->map->map, cube);
	mlx_loop_hook(cube->mlx, ft_general, cube);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop_hook(cube->mlx, ft_render, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	return (0);
}
