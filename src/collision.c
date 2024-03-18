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

bool	touch_wall(char **map, int size, int x, int y)
{
	if (size == 1)
		return (ft_strchr("1D", map[y / SIZE][x / SIZE]));
	x -= size / 2;
	y -= size / 2;
	if (ft_strchr("1D", map[y / SIZE][x / SIZE]))
		return (true);
	if (ft_strchr("1D", map[(y + size - 1) / SIZE][x / SIZE]))
		return (true);
	if (ft_strchr("1D", map[y / SIZE][(x + size - 1) / SIZE]))
		return (true);
	return (ft_strchr("1D", map[(y + size - 1) / SIZE][(x + size - 1) / SIZE]));
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
