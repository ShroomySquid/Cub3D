/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/06 11:26:39 by fbarrett         ###   ########.fr       */
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

int	check_map(t_cube *cube)
{
	int	x;
	int	y;
	int	is_player;

	y = -1;
	is_player = 0;
	while (cube->map->map[++y])
	{
		x = -1;
		while (cube->map->map[y][++x])
		{
			if (ft_strchr("NSWE", cube->map->map[y][x]))
			{
				if (cube->map->map[y][x] == 'N')
					cube->rotation = 0;
				if (cube->map->map[y][x] == 'E')
					cube->rotation = 90;
				if (cube->map->map[y][x] == 'S')
					cube->rotation = 180;
				if (cube->map->map[y][x] == 'W')
					cube->rotation = 270;
				if (is_player)
					return (error_map("More than 1 player"));
				is_player = 1;
				if (check_valid_floor(cube->map->map, x, y))
					return (error_map("Invalid player location"));
			}
			else if (cube->map->map[y][x] == '0' && check_valid_floor(cube->map->map, x, y))
				return (error_map("Invalid floor location"));
			else if (!is_whitespace(cube->map->map[y][x]) && cube->map->map[y][x] != '1' && cube->map->map[y][x] != '0')
			{
				printf("symbol: %c, y: %d, x: %d\n", cube->map->map[y][x], y, x);
				return (error_map("Invalid symbol on map"));
			}
		}
	}
	return (0);
}
