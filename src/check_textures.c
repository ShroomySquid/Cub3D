/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 14:05:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
	if (cube->map->NO && cube->map->SO && cube->map->WE && cube->map->EA
		&& cube->map->roof != -1 && cube->map->floor != -1)
		*valid_map = 1;
}

int	check_cardinals(mlx_image_t **data, char *temp_line,
	int *valid_map, t_cube *cube)
{
	mlx_texture_t	*texture;
	int				i;

	if (*data)
		return (error_map("Multiple textures files for same element"));
	i = 0;
	while (!is_whitespace(temp_line[i + 3]))
		i++;
	if (temp_line[i + 3])
		temp_line[i + 3] = '\0';
	texture = mlx_load_png(&temp_line[3]);
	if (!texture)
		return (error_func("mlx_load_png"));
	*data = mlx_texture_to_image(cube->mlx, texture);
	if (!*data)
		return (error_func("mlx_texture_to_image"));
	mlx_delete_texture(texture);
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
		return (check_fc(&cube->map->floor, temp_line, valid_map, cube));
	else if (ft_strnstr(temp_line, "C ", 2))
		return (check_fc(&cube->map->roof, temp_line, valid_map, cube));
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
		free(temp_line);
		if (data_type && !valid_map)
			return (close(cube->map->fd), error_map("Invalid data"));
	}
	return (0);
}
