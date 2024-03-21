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

void	step_collision(float rotation, t_cube *cube, float speed)
{
	const float	oldy = cube->playery;
	const float	oldx = cube->playerx;

	calculate_step(rotation, cube);
	cube->playerx += cube->step_x * speed;
	if (touch_wall(cube->map->map, 5, cube->playerx, cube->playery))
		cube->playerx = oldx;
	cube->playery += cube->step_y * speed;
	if (touch_wall(cube->map->map, 5, cube->playerx, cube->playery))
		cube->playery = oldy;
}
