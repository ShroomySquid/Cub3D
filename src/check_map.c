/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/18 08:35:15 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	check_valid_floor(char **map, int x, int y)
{
	if (y == 0 || x == 0)
		return (1);
	if (is_whitespace(map[y - 1][x]))
		return (1);
	if (!map[y - 1][x - 1] || is_whitespace(map[y - 1][x - 1]))
		return (1);
	if (!map[y - 1][x + 1] || is_whitespace(map[y - 1][x + 1]))
		return (1);
	if (!map[y + 1] || is_whitespace(map[y + 1][x]))
		return (1);
	if (!map[y + 1][x - 1] || is_whitespace(map[y + 1][x - 1]))
		return (1);
	if (!map[y + 1][x + 1] || is_whitespace(map[y + 1][x + 1]))
		return (1);
	if (is_whitespace(map[y][x - 1]))
		return (1);
	if (!map[y][x + 1] || is_whitespace(map[y][x + 1]))
		return (1);
	return (0);
}

int	is_valid_symbol(char **map, int y, int x)
{
	if (ft_strchr("\n NSWE0D1", map[y][x]))
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
		return (error_map("More than 1 player"));
	*player = 1;
	cube->playerx = (SIZE * x) + 5;
	cube->playery = (SIZE * y) + 5;
	if (check_valid_floor(cube->map->map, x, y))
		return (error_map("Invalid player location"));
	return (0);
}

int	check_map(char **map, t_cube *cube, int x, int y)
{
	int	player;

	y = -1;
	player = 0;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_valid_symbol(map, y, x))
				return (error_map("Invalid symbol on map"));
			else if (check_player(&player, cube, y, x))
				return (1);
			else if ((map[y][x] == '0' || map[y][x] == 'D')
				&& check_valid_floor(map, x, y))
			{
				printf("%d, %d\n", x, y);
				return (error_map("Invalid floor location"));
			}
		}
	}
	cube->last_line = (y - 1);
	if (!player)
		return (error_map("Invalid player location"));
	return (0);
}
