/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/02/28 15:35:54 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

/*
char	**mapcopy(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	copy = ft_calloc((i + 1), sizeof(char));
	if (copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}
*/

static int	*findchar(char **map, char* str)
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
			if (ft_strchr(str, map[mapy][mapx]))
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
	free(pos);
	return (NULL);
}

/*
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
*/

int	check_map(char **map)
{
	//char	**copy;
	int		*pos;

	/*
	copy = mapcopy(map);
	if (!copy)
		return (error_func("ft_calloc"));
	*/
	pos = findchar(map, "NSWE");
	if (!pos)
		return (error_map("Cannot find player character"));	
	free(pos);
	return (0);
}
