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

static void	step_collision(float rotation, t_cube *cube, bool running)
{
	float	oldy;
	float	oldx;

	rotation = fmodf(rotation, 360);
	oldy = cube->playery;
	if (rotation < 90.0)
		cube->playery -= 1.0 / 90.0 * (90.0 - rotation);
	else if (rotation < 180.0)
		cube->playery += (1.0 / 90.0 * rotation) - 1.0;
	else if (rotation < 270.0)
		cube->playery += (1.0 / 90.0 * (90.0 - rotation - 180.0)) + 4.0;
	else
		cube->playery -= (1.0 / 90.0 * (rotation - 180.0)) - 1.0;
	if (touch_wall(cube, cube->playerx, cube->playery))
		cube->playery = oldy;
	oldx = cube->playerx;
	if (rotation < 90.0)
		cube->playerx += 1.0 / 90.0 * rotation;
	else if (rotation < 180.0)
		cube->playerx += 2.0 - (1.0 / 90.0 * rotation);
	else if (rotation < 270.0)
		cube->playerx -= 1.0 / 90.0 * (rotation - 180.0);
	else
		cube->playerx -= 2.0 - (1.0 / 90.0 * (rotation - 180.0));
	if (touch_wall(cube, cube->playerx, cube->playery))
		cube->playerx = oldx;
	if (running)
		step_collision(rotation, cube, false);
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
		step_collision(cube->rotation, cube, running);
	else if (up && !left && !down && right)
		step_collision(cube->rotation + 45, cube, running);
	else if ((!up && !left && !down && right) || (up && !left && down && right))
		step_collision(cube->rotation + 90, cube, running);
	else if (!up && !left && down && right)
		step_collision(cube->rotation + 135, cube, running);
	else if ((!up && !left && down && !right) || (!up && left && down && right))
		step_collision(cube->rotation + 180, cube, running);
	else if (!up && left && down && !right)
		step_collision(cube->rotation + 225, cube, running);
	else if ((!up && left && !down && !right) || (up && left && down && !right))
		step_collision(cube->rotation + 270, cube, running);
	else if (up && left && !down && !right)
		step_collision(cube->rotation + 315, cube, running);
}

void	ft_player(void *param)
{
	t_cube	*cube;

	cube = param;
	ft_movement(mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT), cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT) && ++cube->rotation >= 360)
		cube->rotation = 0;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT) && --cube->rotation < 0)
		cube->rotation = 359;
	cube->player->instances[0].x = cube->playerx;
	cube->player->instances[0].y = cube->playery;
}

void	ft_general(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);
}
