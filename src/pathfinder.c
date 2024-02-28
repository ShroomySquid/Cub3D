/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2023/12/05 21:33:28 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static char	**mapcopy(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	copy = malloc((i + 1) * 8);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

static int	*findchar(char **map, char c, char c2)
{
	int	mapx;
	int	mapy;
	int	*pos;

	mapx = 0;
	mapy = 0;
	pos = malloc(sizeof(int) * 2);
	while (map[mapy])
	{
		while (map[mapy][mapx])
		{
			if (map[mapy][mapx] == c || map[mapy][mapx] == c2)
			{
				pos[0] = mapx;
				pos[1] = mapy;
				return (pos);
			}
			mapx++;
		}
		mapy++;
		mapx = 0;
	}
	pos[0] = -1;
	pos[1] = -1;
	return (pos);
}

static int	checkpath(char **map)
{
	int	*pos;

	pos = findchar(map, 'E', 'C');
	free_all(map);
	if (pos[0] == -1)
	{
		free(pos);
		return (1);
	}
	else
	{
		free(pos);
		return (0);
	}
}

static void	flag(char **map, int x, int y)
{
	map[y][x] = '3';
	if (map[y + 1][x] == '0' || map[y + 1][x] == 'E' || map[y + 1][x] == 'C'
		|| map[y + 1][x] == 'M')
		map[y + 1][x] = '2';
	if (map[y - 1][x] == '0' || map[y - 1][x] == 'E' || map[y - 1][x] == 'C'
		|| map[y + 1][x] == 'M')
		map[y - 1][x] = '2';
	if (map[y][x + 1] == '0' || map[y][x + 1] == 'E' || map[y][x + 1] == 'C'
		|| map[y + 1][x] == 'M')
		map[y][x + 1] = '2';
	if (map[y][x - 1] == '0' || map[y][x - 1] == 'E' || map[y][x - 1] == 'C'
		|| map[y + 1][x] == 'M')
		map[y][x - 1] = '2';
}

int	pathfinder(char **map)
{
	char	**copy;
	int		*pos;

	copy = mapcopy(map);
	pos = findchar(copy, 'P', 'P');
	flag(copy, pos[0], pos[1]);
	while (pos[0] != -1)
	{
		free(pos);
		pos = findchar(copy, '2', '2');
		if (pos[0] != -1)
			flag(copy, pos[0], pos[1]);
	}
	free(pos);
	return (checkpath(copy));
}
