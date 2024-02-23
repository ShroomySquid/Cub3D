/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/23 11:25:17 by fbarrett         ###   ########.fr       */
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

void	set_map(t_cube *cube, int *map)
{
	(void)map;
	uint32_t x;
	uint32_t y;
	int r;
	int g;
	int b;
	int a;

	x = 0;
	y = 0;
	r = 0;
	g = 255;
	b = 255;
	a = 64;
	while (x < cube->map->width)
	{
		while (y < cube->map->height)
		{
			mlx_put_pixel(cube->map, x, y, get_rgba(r, g, b, a));
			y++;
		}
		y = 0;
		x++;
	}	
}

int main(int argc, char **argv)
{
	t_cube *cube;
	int map[] = 
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};

	(void)argc;
	(void)argv;
	cube = ft_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (error_msg("ft_calloc"));
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cube->mlx)
		return (error_msg("mlx_init"));
	cube->map = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->map)
		return (error_msg("mlx_new_image"));	
	cube->player = mlx_new_image(cube->mlx, 4, 4);
	if (!cube->player)
		return (error_msg("mlx_new_image"));	
	ft_memset(cube->player->pixels, 255, cube->player->width * cube->player->height * sizeof(int32_t));
	set_map(cube, map);
	mlx_image_to_window(cube->mlx, cube->map, 0, 0);
	mlx_image_to_window(cube->mlx, cube->player, 64, 64);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	return (0);
}
