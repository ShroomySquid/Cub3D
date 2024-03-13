/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/13 11:44:12 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	draw_line(uint32_t middle[2], int angle, t_cube *c)
{
	uint32_t x;
	uint32_t y;

	if (angle == 0)
	{
		y = 0;
		while (y < middle[1])
		{
			mlx_put_pixel(c->player, middle[0], y, get_rgba(255, 255, 255, 255));
			y++;
		}
		return ;
	}
	if (angle == 90)
	{
		x = middle[0];
		while (x <= c->player->width)
		{
			mlx_put_pixel(c->player, x, middle[1], get_rgba(255, 255, 255, 255));
			x++;
		}
		return ;
	}
	if (angle == 180)
	{
		y = middle[1];
		while (y < c->player->height)
		{
			mlx_put_pixel(c->player, middle[0], y, get_rgba(255, 255, 255, 255));
			y++;
		}
		return ;
	}
	if (angle == 270)
	{
		x = 0;
		while (x < middle[0])
		{
			mlx_put_pixel(c->player, x, middle[1], get_rgba(255, 255, 255, 255));
			x++;
		}
		return ;
	}
}

void	render_player(void *param)
{
	t_cube *cube;
	uint32_t	x;
	uint32_t	y;
	int left;
	uint32_t right;
	uint32_t middle[2];

	cube = param;
	left = cube->rotation - 30;
	if (left < 0)
		left += 360;
	right = cube->rotation + 30;
	if (right > 360)
		right -= 360;
	middle[0] = cube->player->width / 2;
	middle[1] = cube->player->height / 2;
	draw_line(middle, left, cube);
	draw_line(middle, right, cube);
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
	draw_line(middle, left, cube);
	draw_line(middle, right, cube);
}
