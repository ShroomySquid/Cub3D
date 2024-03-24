/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:18:09 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 09:34:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int	is_max_length(t_cube *c, unsigned int y, unsigned int x)
{
	return (y < 0 || y >= c->player->height || x < 0 || x >= c->player->width);
}

static	int	check_corners_mini(t_cube *c, float last_x, float last_y)
{
	int	x;
	int	y;
	int	m_x;
	int	m_y;

	x = (int)(last_x / 32);
	y = (int)(last_y / 32);
	reverse_step(&last_x, &last_y, c, 1);
	m_x = (int)(last_x / 32);
	m_y = (int)(last_y / 32);
	if (x != m_x && y != m_y)
	{
		if (m_x < x && m_y < y && (c->map->map[m_y + 1][m_x] == '1'
			|| c->map->map[m_y][m_x + 1] == '1'))
			return (1);
		if (m_x < x && m_y > y && (c->map->map[m_y - 1][m_x] == '1'
			|| c->map->map[m_y][m_x + 1] == '1'))
			return (1);
		if (m_x > x && m_y > y && (c->map->map[m_y - 1][m_x] == '1'
			|| c->map->map[m_y][m_x - 1] == '1'))
			return (1);
		if (m_x > x && m_y < y && (c->map->map[m_y + 1][m_x] == '1'
			|| c->map->map[m_y][m_x - 1] == '1'))
			return (1);
	}
	return (0);
}

static void	draw_line(float angle, t_cube *c)
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
	while (!is_max_length(c, y, x) && i < 240)
	{
		mlx_put_pixel(c->player, x, y, get_rgba(255, 255, 255, 240 - i));
		step(&map_x, &map_y, c, 1);
		step(&x, &y, c, 1);
		i += 1;
		if (touch_wall(c->map->map, 1, map_x, map_y))
			return ;
		if (check_corners_mini(c, map_x, map_y))
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
		i += (1.0 / 5);
		los += (1.0 / 5);
		if (los >= 360)
			los = 0;
	}
}
