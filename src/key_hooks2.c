/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:28:22 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/22 17:56:13 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	ft_mouse_next(t_cube *c, int x)
{
	float	move;

	if (x - (float)c->mlx->width / 2)
		move = (sqrtf(fabsf(x - (float)c->mlx->width / 2)) - 1)
			* c->mlx->delta_time * 60;
	if (x - (float)c->mlx->width / 2 < 0)
		move = -move;
	if (move)
		c->rotation += move;
	c->rotation = fmodf(c->rotation, 360) + (c->rotation < 0) * 360;
	mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
}

void	ft_mouse(t_cube *c)
{
	static int	init = 2;
	int			x;
	int			y;

	if (init)
	{
		mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
		init--;
		return ;
	}
	mlx_get_mouse_pos(c->mlx, &x, &y);
	if ((x == c->mlx->width / 2 && y == c->mlx->height / 2) || x < 0
		|| x > c->mlx->width || y < 0 || y > c->mlx->height)
		return ;
	c->draw_screen = true;
	c->draw_player = true;
	ft_mouse_next(c, x);
}

static void	ft_movement_innit(t_mov *m, bool running, t_cube *cube)
{
	m->down = (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_S));
	m->left = mlx_is_key_down(cube->mlx, MLX_KEY_A);
	m->right = mlx_is_key_down(cube->mlx, MLX_KEY_D);
	m->up = (mlx_is_key_down(cube->mlx, MLX_KEY_UP)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_W));
	m->speed = cube->mlx->delta_time * 60;
	if (running)
		m->speed *= 2;
}

void	ft_movement(bool running, t_cube *cube)
{
	t_mov	m;

	ft_movement_innit(&m, running, cube);
	if ((m.up && !m.left && !m.down && !m.right)
		|| (m.up && m.left && !m.down && m.right))
		step_collision(fmodf(cube->rotation, 360), cube, m.speed);
	else if (m.up && !m.left && !m.down && m.right)
		step_collision(fmodf(cube->rotation + 45, 360), cube, m.speed);
	else if ((!m.up && !m.left && !m.down && m.right)
		|| (m.up && !m.left && m.down && m.right))
		step_collision(fmodf(cube->rotation + 90, 360), cube, m.speed);
	else if (!m.up && !m.left && m.down && m.right)
		step_collision(fmodf(cube->rotation + 135, 360), cube, m.speed);
	else if ((!m.up && !m.left && m.down && !m.right)
		|| (!m.up && m.left && m.down && m.right))
		step_collision(fmodf(cube->rotation + 180, 360), cube, m.speed);
	else if (!m.up && m.left && m.down && !m.right)
		step_collision(fmodf(cube->rotation + 225, 360), cube, m.speed);
	else if ((!m.up && m.left && !m.down && !m.right)
		|| (m.up && m.left && m.down && !m.right))
		step_collision(fmodf(cube->rotation + 270, 360), cube, m.speed);
	else if (m.up && m.left && !m.down && !m.right)
		step_collision(fmodf(cube->rotation + 315, 360), cube, m.speed);
}
