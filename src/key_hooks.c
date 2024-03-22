/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/19 10:31:51 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	ft_mouse(t_cube *c)
{
	static int	init = 2;
	float		move;
	int			x;
	int			y;

	if (init)
	{
		mlx_set_mouse_pos(c->mlx, c->width_div, c->height_div);
		init--;
		return ;
	}
	mlx_get_mouse_pos(c->mlx, &x, &y);
	if ((x == c->width_div && y == c->height_div) || x < 0 || x > c->mlx->width || y < 0 || y > c->mlx->height)
		return ;
	c->draw_screen = true;
	c->draw_player = true;
	if (x - c->width_div)
		move = (sqrtf(abs(x - c->width_div)) - 1) * c->mlx->delta_time * 60;
	if (x - c->width_div < 0)
		move = -move;
	if (move)
		c->rotation += move;
	mlx_set_mouse_pos(c->mlx, c->width_div, c->height_div);
}

static void	ft_movement(bool running, t_cube *cube)
{
	const bool	down = (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_S));
	const bool	left = mlx_is_key_down(cube->mlx, MLX_KEY_A);
	const bool	right = mlx_is_key_down(cube->mlx, MLX_KEY_D);
	const bool	up = (mlx_is_key_down(cube->mlx, MLX_KEY_UP)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_W));
	float		speed;

	speed = cube->mlx->delta_time * 60;
	if (running)
		speed *= 2;
	if ((up && !left && !down && !right) || (up && left && !down && right))
		step_collision(fmodf(cube->rotation, 360), cube, speed);
	else if (up && !left && !down && right)
		step_collision(fmodf(cube->rotation + 45, 360), cube, speed);
	else if ((!up && !left && !down && right) || (up && !left && down && right))
		step_collision(fmodf(cube->rotation + 90, 360), cube, speed);
	else if (!up && !left && down && right)
		step_collision(fmodf(cube->rotation + 135, 360), cube, speed);
	else if ((!up && !left && down && !right) || (!up && left && down && right))
		step_collision(fmodf(cube->rotation + 180, 360), cube, speed);
	else if (!up && left && down && !right)
		step_collision(fmodf(cube->rotation + 225, 360), cube, speed);
	else if ((!up && left && !down && !right) || (up && left && down && !right))
		step_collision(fmodf(cube->rotation + 270, 360), cube, speed);
	else if (up && left && !down && !right)
		step_collision(fmodf(cube->rotation + 315, 360), cube, speed);
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
	ft_movement(mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT) || mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT_SHIFT), cube);
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
