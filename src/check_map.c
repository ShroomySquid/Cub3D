/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/04/02 10:03:33 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	check_valid_floor(char **map, int x, int y)
{
	if (y == 0 || x == 0)
		return (1);
	if (x > (int)ft_strlen(map[y - 1]) || is_whitespace(map[y - 1][x]))
		return (1);
	if (!map[y + 1] || x > (int)ft_strlen(map[y + 1])
		|| is_whitespace(map[y + 1][x]))
		return (1);
	if (is_whitespace(map[y][x - 1]))
		return (1);
	if (!map[y][x + 1] || is_whitespace(map[y][x + 1]))
		return (1);
	return (0);
}

int	check_valid_door(char **map, int x, int y)
{
	if (check_valid_floor(map, x, y))
		return (1);
	if (map[y - 1][x] == '1')
	{
		if (map[y + 1][x] != '1' || map[y][x + 1] == '1'
			|| map[y][x + 1] == 'D' || map[y][x - 1] == '1'
			|| map[y][x - 1] == 'D')
			return (1);
		else
			return (0);
	}
	else if (map[y][x - 1] == '1')
	{
		if (map[y][x + 1] != '1' || map[y - 1][x] == '1'
			|| map[y - 1][x] == 'D' || map[y + 1][x] == '1'
			|| map[y - 1][x] == 'D')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	is_valid_symbol(char **map, int y, int x)
{
	if (is_whitespace(map[y][x]) || ft_strchr("NSWE0D1", map[y][x]))
		return (0);
	return (1);
}

int	check_player(int *player, t_cube *cube, int y, int x)
{
	if (!ft_strchr("NSWE", cube->map->map[y][x]))
		return (0);
	if (cube->map->map[y][x] == 'N')
		cube->rotation = 0;
	if (cube->map->map[y][x] == 'E')
		cube->rotation = 90;
	if (cube->map->map[y][x] == 'S')
		cube->rotation = 180;
	if (cube->map->map[y][x] == 'W')
		cube->rotation = 270;
	if (*player)
		return (error_map("More than 1 player", x, y));
	*player = 1;
	cube->playerx = (SIZE * x) + 5;
	cube->playery = (SIZE * y) + 5;
	if (check_valid_floor(cube->map->map, x, y))
		return (error_map("Invalid player location", x, y));
	return (0);
}

int	check_map(char **map, t_cube *cube, int x, int y)
{
	int	player;

	y = 0;
	player = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_valid_symbol(map, y, x))
				return (error_map("Invalid symbol on map", x, y));
			else if (check_player(&player, cube, y, x))
				return (1);
			else if (map[y][x] == '0' && check_valid_floor(map, x, y))
				return (error_map("Invalid floor location", x, y));
			else if (map[y][x] == 'D' && check_valid_door(map, x, y))
				return (error_map("Invalid door location", x, y));
			x++;
		}
		y++;
	}
	cube->last_line = (y - 1);
	if (!player)
		return (error_map("Invalid player location", x, y));
	return (0);
}
