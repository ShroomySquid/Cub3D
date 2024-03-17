/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/15 10:18:23 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	innit_map_struct(t_cube *cube)
{
	cube->map->walls[0] = NULL;
	cube->map->walls[1] = NULL;
	cube->map->walls[2] = NULL;
	cube->map->walls[3] = NULL;
	cube->map->walls[4] = NULL;
	cube->map->walls[5] = NULL;
	cube->map->floor = -1;
	cube->map->roof = -1;
}

void	is_map_still_invalid(int *valid_map, t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->map->walls[i])
		i++;
	if (i != 5)
		return ;
	if (cube->map->roof != -1 && cube->map->floor != -1)
		*valid_map = 1;
}

int	check_each_token(char **data, t_cube *cube)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (is_cardinal(data[i], cube) > -1)
		{
			i++;
			if (check_cardinals(data[i], cube))
				return (1);
		}
		else if (data[i] && (ft_strnstr(data[i], "F", 2)
				|| ft_strnstr(data[i], "C", 2)))
		{
			i++;
			if (check_fc(&i, data, cube))
				return (1);
		}
		if (data[i])
			i++;
	}
	return (0);
}

int	check_data_type(char *temp_line, int *valid_map, t_cube *cube)
{
	char	**data;
	char	*whitespaces;

	if (is_whitespace_str(temp_line))
		return (0);
	whitespaces = whitespace_array();
	data = ft_split(temp_line, whitespaces);
	free(whitespaces);
	if (check_each_token(data, cube))
		return (free_all(data), 1);
	free_all(data);
	return (is_map_still_invalid(valid_map, cube), 0);
}

int	check_textures(t_cube *cube)
{
	char	*temp_line;
	int		valid_map;
	char	data_type;

	innit_map_struct(cube);
	if (!cube->map->walls)
		return (close(cube->map->fd), error_func("malloc"));
	valid_map = 0;
	while (!valid_map)
	{
		temp_line = get_next_line(cube->map->fd);
		cube->map->nbr_line -= 1;
		if (!temp_line)
			return (close(cube->map->fd), error_func("GNL"));
		data_type = check_data_type(temp_line, &valid_map, cube);
		free(temp_line);
		if (data_type && !valid_map)
			return (close(cube->map->fd), error_map("Invalid data"));
	}
	return (0);
}
