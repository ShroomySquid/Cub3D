/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 13:18:16 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	ft_player(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_UP) || mlx_is_key_down(cube->mlx,
			MLX_KEY_W))
		step(&cube->playerx, &cube->playery, cube->rotation, 2);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN) || mlx_is_key_down(cube->mlx,
			MLX_KEY_S))
		step(&cube->playerx, &cube->playery, cube->rotation + 180, 2);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->rotation -= 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
		step(&cube->playerx, &cube->playery, cube->rotation + 270, 2);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->rotation += 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
		step(&cube->playerx, &cube->playery, cube->rotation + 90, 2);
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
