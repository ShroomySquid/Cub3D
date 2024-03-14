/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/13 13:48:30 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void draw_line(float angle, t_cube *cube)
{
	float	x;
	float	y;
	int		i;

	y = (float)cube->player->height / 2;
	x = (float)cube->player->width / 2;
	i = 0;
	while (x > 0 && x < cube->player->width && y > 0 && y < cube->player->height && i < 240)
	{
		mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 255 - i));
		step(&x, &y, angle);
		i += 12;
	}
}

void	render_player(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	uint32_t	y;
	int			los;
	int			i;

	cube = param;
	los = cube->rotation - 30;
	if (los < 0)
		los += 360;
	i = 0;
	x = 0;
	y = 0;
	while (x < cube->player->width)
	{
		while (y < cube->player->height)
		{
			if (y > 12 && y < 18 && x > 12 && x < 18)
				mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 255));
			else
				mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 0));
			y++;
		}
		y = 0;
		x++;
	}
	while (i < 60)
	{
		draw_line(los, cube);
		i++;
		los += 1;
		if (los >= 360)
			los = 0;
	}
}
