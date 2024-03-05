/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/05 17:48:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	innit_map_struct(t_cube *cube)
{
	cube->map->NO = NULL;
	cube->map->SO = NULL;
	cube->map->WE = NULL;
	cube->map->EA = NULL;
	cube->map->floor = NULL;
	cube->map->roof = NULL;
}

void	is_map_still_invalid(int *valid_map, t_cube *cube)
{
	if (cube->map->NO && cube->map->SO &&cube->map->WE &&cube->map->EA
		&& cube->map->roof && cube->map->floor)
		*valid_map = 1;
}

int	check_data_type(char *temp_line, int *valid_map, t_cube *cube)
{
	if (ft_strnstr(temp_line, "NO", 2))
	{
		if (cube->map->NO)
			return (0);
		cube->map->NO = ft_strdup(temp_line);
		if (!cube->map->NO)
			return (error_func("ft_strdup"), 0);
		return (is_map_still_invalid(valid_map, cube), 1);
	}
	else if (ft_strnstr(temp_line, "SO", 2))
	{
		if (cube->map->SO)
			return (0);
		cube->map->SO = ft_strdup(temp_line);
		if (!cube->map->SO)
			return (error_func("ft_strdup"), 0);
		return (is_map_still_invalid(valid_map, cube), 1);
	}
	else if (ft_strnstr(temp_line, "WE", 2))
	{
		if (cube->map->WE)
			return (0);
		cube->map->WE = ft_strdup(temp_line);
		if (!cube->map->WE)
			return (error_func("ft_strdup"), 0);
		return (is_map_still_invalid(valid_map, cube), 1);
	}
	else if (ft_strnstr(temp_line, "EA", 2))
	{
		if (cube->map->EA)
			return (0);
		cube->map->EA = ft_strdup(temp_line);
		if (!cube->map->EA)
			return (error_func("ft_strdup"), 0);
		return (is_map_still_invalid(valid_map, cube), 1);
	}
	else if (ft_strnstr(temp_line, "F", 1))
	{
		if (cube->map->floor)
			return (0);
		cube->map->floor = ft_strdup(temp_line);
		if (!cube->map->floor)
			return (error_func("ft_strdup"), 0);
		return (is_map_still_invalid(valid_map, cube), 1);
	}
	else if (ft_strnstr(temp_line, "C", 1))
	{
		if (cube->map->roof)
			return (0);
		cube->map->roof = ft_strdup(temp_line);
		if (!cube->map->roof)
			return (error_func("ft_strdup"), 0);
		return (is_map_still_invalid(valid_map, cube), 1);
	}
	return (0);
}

char *check_textures(t_cube *cube)
{
	char	*temp_line;
	int		valid_map;
	char	data_type;

	innit_map_struct(cube);
	valid_map = 0;
	while (!valid_map)
	{
		temp_line = get_next_line(cube->map->fd);
		cube->map->nbr_line -= 1;
		if (!temp_line)
			return (error_func("GNL"), close(cube->map->fd), NULL);
		data_type = check_data_type(temp_line, &valid_map, cube);
		if (!valid_map)
			free(temp_line);
		if (!data_type && !valid_map)
		{
			return (error_map("Invalid data in .cub file"), close(cube->map->fd), NULL);	
		}
	}
	cube->map->nbr_line += 1;
	return (temp_line);
}
