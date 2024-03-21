/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:10:03 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/19 11:20:52 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static bool	ft_collision(char **map, int x, int y)
{
	const int	y_div = y / SIZE;
	const int	x_div = x / SIZE;
	const int	size_div = SIZE / 2;
	const int	size_div2 = SIZE / 8;

	if (map[y_div][x_div] == '1')
		return (true);
	if (map[y_div][x_div] == 'D')
	{
		if (map[y_div][x_div - 1] == '1' || map[y_div][x_div + 1] == '1')
			return (y % SIZE > size_div - size_div2 && y % SIZE < size_div + size_div2);
		if (map[y_div - 1][x_div] == '1' || map[y_div + 1][x_div] == '1')
			return (x % SIZE > size_div - size_div2 && x % SIZE < size_div + size_div2);
		return (true);
	}
	return (false);
}

bool	touch_wall(char **map, int size, int x, int y)
{
	const int	size_div = size / 2;

	if (size == 1)
		return (ft_collision(map, x, y));
	x -= size_div;
	y -= size_div;
	if (ft_collision(map, x, y))
		return (true);
	if (ft_collision(map, x, y + size - 1))
		return (true);
	if (ft_collision(map, x + size - 1, y))
		return (true);
	return (ft_collision(map, x + size - 1, y + size - 1));
}

void	step_collision(float rotation, t_cube *cube, float speed)
{
	const float	oldy = cube->playery;
	const float	oldx = cube->playerx;

	calculate_step(rotation, cube);
	cube->playerx += cube->step_x * speed;
	if (touch_wall(cube->map->map, 5, cube->playerx, cube->playery))
		cube->playerx = oldx;
	else
	{
		cube->draw_map = true;
		cube->draw_player = true;
		cube->draw_screen = true;
	}
	cube->playery += cube->step_y * speed;
	if (touch_wall(cube->map->map, 5, cube->playerx, cube->playery))
		cube->playery = oldy;
	else
	{
		cube->draw_map = true;
		cube->draw_player = true;
		cube->draw_screen = true;
	}
}
