/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 13:25:29 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

bool	touch_wall(char **map, int size, int x, int y)
{
	if (size == 1)
		return (map[y / 32][x / 32] == '1');
	x -= size / 2;
	y -= size / 2;
	if (map[y / 32][x / 32] == '1')
		return (true);
	if (map[(y + size - 1) / 32][x / 32] == '1')
		return (true);
	if (map[y / 32][(x + size - 1) / 32] == '1')
		return (true);
	if (map[(y + size - 1) / 32][(x + size - 1) / 32] == '1')
		return (true);
	return (false);
}

static void	step_collision(float rotation, t_cube *cube, bool running)
{
	const float	oldy = cube->playery;
	const float	oldx = cube->playerx;

	if (rotation < 90.0)
		cube->playery -= 1.0 / 90.0 * (90.0 - rotation);
	else if (rotation < 180.0)
		cube->playery += (1.0 / 90.0 * rotation) - 1.0;
	else if (rotation < 270.0)
		cube->playery += (1.0 / 90.0 * (90.0 - rotation - 180.0)) + 4.0;
	else
		cube->playery -= (1.0 / 90.0 * (rotation - 180.0)) - 1.0;
	if (touch_wall(cube->map->map, 5, cube->playerx, cube->playery))
		cube->playery = oldy;
	if (rotation < 90.0)
		cube->playerx += 1.0 / 90.0 * rotation;
	else if (rotation < 180.0)
		cube->playerx += 2.0 - (1.0 / 90.0 * rotation);
	else if (rotation < 270.0)
		cube->playerx -= 1.0 / 90.0 * (rotation - 180.0);
	else
		cube->playerx -= 2.0 - (1.0 / 90.0 * (rotation - 180.0));
	if (touch_wall(cube->map->map, 5, cube->playerx, cube->playery))
		cube->playerx = oldx;
	if (running)
		step_collision(rotation, cube, false);
}

static void	ft_mouse(t_cube *c)
{
	static bool	first;
	int			newx;
	int			newy;

	if (first)
	{
		mlx_set_mouse_pos(c->mlx, c->mlx->width / 2, c->mlx->height / 2);
		first = true;
		return ;
	}
	mlx_get_mouse_pos(c->mlx, &newx, &newy);
	c->rotation += (newx - c->mlx->width / 2) / 4;
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
