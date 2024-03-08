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

static void	step_collision(float rotation, t_cube *cube)
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
}

void	ft_player(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_UP) || mlx_is_key_down(cube->mlx,
			MLX_KEY_W))
		step_collision(cube->rotation, cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN) || mlx_is_key_down(cube->mlx,
			MLX_KEY_S))
		step_collision(cube->rotation + 180, cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		if (--cube->rotation < 0)
			cube->rotation = 359;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
		step_collision(cube->rotation + 270, cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		if (++cube->rotation >= 360)
			cube->rotation = 0;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
		step_collision(cube->rotation + 90, cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT) || mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		printf("rotation: %d\n", cube->rotation);
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
