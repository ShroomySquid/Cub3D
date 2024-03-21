/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/19 12:54:43 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	is_max_length(t_cube *c, unsigned int y, unsigned int x)
{
	return (y < 0 || y >= c->player->height || x < 0 || x >= c->player->width);
}

void	draw_line(float angle, t_cube *c)
{
	float	x;
	float	y;
	float	map_x;
	float	map_y;
	int		i;

	y = (float)c->player->height / 2;
	x = (float)c->player->width / 2;
	i = 0;
	map_x = c->playerx;
	map_y = c->playery;
	calculate_step(angle, c);
	while (!is_max_length(c, y, x) && i < 224)
	{
		mlx_put_pixel(c->player, x, y, get_rgba(255, 255, 255, 240 - i));
		step(&map_x, &map_y, c, 1);
		step(&x, &y, c, 1);
		i += 1;
		if (touch_wall(c->map->map, 1, map_x, map_y))
			return ;
	}
}

void	draw_los(float los, t_cube *cube)
{
	float	i;

	i = 0;
	while (!is_mini_down(cube) && i < FOV)
	{
		draw_line(los, cube);
		i += (1.0 / 6);
		los += (1.0 / 6);
		if (los >= 360)
			los = 0;
	}
}

void	render_player(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	uint32_t	y;
	int			los;

	cube = param;
	if (!cube->draw_player)
		return ;
	los = cube->rotation - (FOV / 2.0);
	if (los < 0)
		los += 360;
	x = 0;
	y = 0;
	while (x < cube->player->width)
	{
		while (y < cube->player->height)
		{
			if (!is_mini_down(cube) && y > 109 && y < 115 && x > 109 && x < 115)
				mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 255));
			else
				mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 0));
			y++;
		}
		y = 0;
		x++;
	}
	if (cube->is_light_active)
		draw_los(los, cube);
	cube->draw_player = false;
}
