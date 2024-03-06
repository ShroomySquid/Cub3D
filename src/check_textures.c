/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/06 11:23:33 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	print_data(t_cube *cube)
{
	printf("NO: %s\n", cube->map->NO);
	printf("SO: %s\n", cube->map->SO);
	printf("WE: %s\n", cube->map->WE);
	printf("EA: %s\n", cube->map->EA);
	printf("floor: %d\n", cube->map->floor);
	printf("roof: %d\n", cube->map->roof);
}

void	innit_map_struct(t_cube *cube)
{
	cube->map->NO = NULL;
	cube->map->SO = NULL;
	cube->map->WE = NULL;
	cube->map->EA = NULL;
	cube->map->floor = -1;
	cube->map->roof = -1;
}

void	is_map_still_invalid(int *valid_map, t_cube *cube)
{
	if (cube->map->NO && cube->map->SO &&cube->map->WE &&cube->map->EA
		&& cube->map->roof != -1 && cube->map->floor != -1)
		*valid_map = 1;
}

int	check_cardinals(char **data, char *temp_line, int *valid_map, t_cube *cube)
{
	if (*data)
		return (1);
	*data = ft_strdup(&temp_line[3]);
	if (!*data)
		return (error_func("ft_strdup"));
	return (is_map_still_invalid(valid_map, cube), 0);
}

int	check_FC(int *data, char *temp_line, int *valid_map, t_cube *cube)
{
	int 	*rgb;
	char	*temp_color;
	int		i;
	int 	len;
	int		a;

	if (*data != -1)
		return (1);
	rgb = malloc(sizeof(int) * 4);
	if (!rgb)
		return (error_func("malloc"));
	i = 2;
	a = 0;
	while (a < 3)
	{
		len = 0;
		while (temp_line[i + len] && temp_line[i + len] != ',' && temp_line[i + len] != '\n')
			len++;
		if (len > 3 || len < 1)
			return (free(rgb), error_map("Invalid color length for rgb"));
		temp_color = ft_substr(temp_line, i, len);
		if (!temp_color)
			return (free(rgb), error_func("ft_substr"));
		printf("%s\n", temp_color);
		if (!is_digit_str(temp_color))
			return (free(rgb), free(temp_color), error_map("Invalid color for rgb"));
		rgb[a] = ft_atoi(temp_color);
		if (rgb[a] > 255 || rgb[a] < 0)
			return (free(rgb), free(temp_color), error_map("Invalid color for rgb"));
		a++;
		i += len + 1;
		free(temp_color);
	}
	*data = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free(rgb);
	return (is_map_still_invalid(valid_map, cube), 0);
}


int	check_data_type(char *temp_line, int *valid_map, t_cube *cube)
{
	if (is_whitespace_str(temp_line))
		return (0);
	else if (ft_strnstr(temp_line, "NO ", 3))
		return (check_cardinals(&cube->map->NO, temp_line, valid_map, cube));
	else if (ft_strnstr(temp_line, "SO ", 3))
		return (check_cardinals(&cube->map->SO, temp_line, valid_map, cube));
	else if (ft_strnstr(temp_line, "WE ", 3))
		return (check_cardinals(&cube->map->WE, temp_line, valid_map, cube));
	else if (ft_strnstr(temp_line, "EA ", 3))
		return (check_cardinals(&cube->map->EA, temp_line, valid_map, cube));
	else if (ft_strnstr(temp_line, "F ", 2))
		return (check_FC(&cube->map->floor, temp_line, valid_map, cube));
	else if (ft_strnstr(temp_line, "C ", 2))
		return (check_FC(&cube->map->roof, temp_line, valid_map, cube));
	return (1);
}

int	check_textures(t_cube *cube)
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
			return (close(cube->map->fd), error_func("GNL"));
		data_type = check_data_type(temp_line, &valid_map, cube);
		if (!valid_map)
			free(temp_line);
		if (data_type && !valid_map)
			return (close(cube->map->fd), error_map("Invalid data in .cub file"));
	}
	print_data(cube);
	return (0);
}
