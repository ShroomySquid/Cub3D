/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 13:25:29 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	ft_mouse(t_cube *c)
{
	static int	first;
	int			x;
	int			y;

	if (first <= 2)
	{
		mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
		first++;
		return ;
	}
	mlx_get_mouse_pos(c->mlx, &x, &y);
	c->rotation += (x - c->mlx->width / 2) / 4;
	if (c->rotation < 0)
		c->rotation += 360;
	else if (c->rotation >= 360)
		c->rotation %= 360;
	mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
}

static void	ft_movement(bool running, t_cube *cube)
{
	const bool	down = (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_S));
	const bool	left = mlx_is_key_down(cube->mlx, MLX_KEY_A);
	const bool	right = mlx_is_key_down(cube->mlx, MLX_KEY_D);
	const bool	up = (mlx_is_key_down(cube->mlx, MLX_KEY_UP)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_W));

	if ((up && !left && !down && !right) || (up && left && !down && right))
		step_collision(fmodf(cube->rotation, 360), cube, running);
	else if (up && !left && !down && right)
		step_collision(fmodf(cube->rotation + 45, 360), cube, running);
	else if ((!up && !left && !down && right) || (up && !left && down && right))
		step_collision(fmodf(cube->rotation + 90, 360), cube, running);
	else if (!up && !left && down && right)
		step_collision(fmodf(cube->rotation + 135, 360), cube, running);
	else if ((!up && !left && down && !right) || (!up && left && down && right))
		step_collision(fmodf(cube->rotation + 180, 360), cube, running);
	else if (!up && left && down && !right)
		step_collision(fmodf(cube->rotation + 225, 360), cube, running);
	else if ((!up && left && !down && !right) || (up && left && down && !right))
		step_collision(fmodf(cube->rotation + 270, 360), cube, running);
	else if (up && left && !down && !right)
		step_collision(fmodf(cube->rotation + 315, 360), cube, running);
}

void	ft_player(void *param)
{
	t_cube	*cube;

	cube = param;
	ft_mouse(cube);
	ft_movement(mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT), cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT) && ++cube->rotation >= 360)
		cube->rotation = 0;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT) && --cube->rotation < 0)
		cube->rotation = 359;
}

void	ft_general(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
}
