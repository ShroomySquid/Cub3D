/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:10:03 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/18 09:59:32 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static bool	ft_collision(char **map, int x, int y)
{
	if (map[y / SIZE][x / SIZE] == '1')
		return (true);
	if (map[y / SIZE][x / SIZE] == 'D')
	{
		if (map[y / SIZE][(x / SIZE) - 1] == '1' || map[y / SIZE][(x / SIZE) + 1] == '1')
			return (y % SIZE > SIZE / 2 - SIZE / 8 && y % SIZE < SIZE / 2 + SIZE / 8);
		if (map[(y / SIZE) - 1][x / SIZE] == '1' || map[(y / SIZE) + 1][x / SIZE] == '1')
			return (x % SIZE > SIZE / 2 - SIZE / 8 && x % SIZE < SIZE / 2 + SIZE / 8);
		return (true);
	}
	return (false);
}

bool	touch_wall(char **map, int size, int x, int y)
{
	if (size == 1)
		return (ft_collision(map, x, y));
	x -= size / 2;
	y -= size / 2;
	if (ft_collision(map, x, y))
		return (true);
	if (ft_collision(map, x, y + size - 1))
		return (true);
	if (ft_collision(map, x + size - 1, y))
		return (true);
	return (ft_collision(map, x + size - 1, y + size - 1));
}

void	step_collision(float rotation, t_cube *cube, bool running)
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
