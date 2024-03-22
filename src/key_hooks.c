/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/22 16:50:56 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	open_door(t_cube *cube, float x, float y)
{
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
		|| mlx_is_key_down(cube->mlx, MLX_KEY_E))
	{
		calculate_step(cube->rotation, cube);
		while (!touch_wall(cube->map->map, 1, x, y))
			step(&x, &y, cube, 1);
		if (hypotf(fabsf((cube->playery - (int)y)), fabsf(cube->playerx
					- (int)x)) < 113 && cube->map->map[(int)y / SIZE][(int)x
			/ SIZE] == 'D')
		{
			cube->map->map[(int)y / SIZE][(int)x / SIZE] = '0';
			cube->draw_map = true;
			cube->draw_player = true;
			cube->draw_screen = true;
		}
	}
}

void	ft_player(void *param)
{
	t_cube	*cube;
	float	x;
	float	y;

	cube = param;
	x = cube->playerx;
	y = cube->playery;
	ft_mouse(cube);
	ft_movement(mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT)
		|| mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT_SHIFT), cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
	{
		cube->rotation += cube->mlx->delta_time * 60;
		cube->draw_player = true;
		cube->draw_screen = true;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
	{
		cube->rotation -= cube->mlx->delta_time * 60;
		cube->draw_player = true;
		cube->draw_screen = true;
	}
	cube->rotation = fmodf(cube->rotation, 360) + (cube->rotation < 0) * 360;
	open_door(cube, x, y);
}

void	ft_general(mlx_key_data_t data, void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
	if (data.action == MLX_PRESS)
	{
		if (mlx_is_key_down(cube->mlx, MLX_KEY_F))
		{
			if (cube->is_light_active)
				cube->is_light_active = 0;
			else
				cube->is_light_active = 1;
			cube->draw_player = true;
		}
		if (mlx_is_key_down(cube->mlx, MLX_KEY_M))
		{
			if (cube->is_mini_active)
				cube->is_mini_active = 0;
			else
				cube->is_mini_active = 1;
			cube->draw_player = true;
			cube->draw_map = true;
		}
	}
}
