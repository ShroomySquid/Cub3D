/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/14 19:25:58 by fbarrett         ###   ########.fr       */
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
	cube->map->floor = -1;
	cube->map->roof = -1;
}

void	is_map_still_invalid(int *valid_map, t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->map->walls[i])
		i++;
	if (i != 4)
		return ;
	if (cube->map->roof != -1 && cube->map->floor != -1)
		*valid_map = 1;
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	check_cardinals(char *paths, t_cube *c)
{
	mlx_texture_t	*texture;
	int				i;
	char			**split_path;

	if (c->map->walls[c->map->car])
		return (error_map("Multiple textures files for same element"));
	split_path = ft_split(paths, ";");
	if (!split_path)
		return (error_func("ft_split"));
	c->map->walls[c->map->car] = malloc((array_len(split_path) + 1)
			* sizeof(mlx_image_t *));
	if (!c->map->walls[c->map->car])
		return (free_all(split_path), error_func("malloc"));
	i = 0;
	if (!split_path[i])
		return (free_all(split_path), error_map("No texture file for element"));
	while (split_path[i])
	{
		texture = mlx_load_png(split_path[i]);
		if (!texture)
			return (free_all(split_path), error_func("mlx_load_png"));
		c->map->walls[c->map->car][i] = mlx_texture_to_image(c->mlx, texture);
		if (!c->map->walls[c->map->car][i])
			return (free_all(split_path), error_func("mlx_texture_to_image"));
		mlx_delete_texture(texture);
		i++;
	}
	free_all(split_path);
	c->map->walls[c->map->car][i] = NULL;
	return (0);
}

int	is_cardinal(char *str, t_cube *cube)
{
	if (!ft_strncmp(str, "NO", 3))
		cube->map->car = 0;
	else if (!ft_strncmp(str, "SO", 3))
		cube->map->car = 1;
	else if (!ft_strncmp(str, "WE", 3))
		cube->map->car = 2;
	else if (!ft_strncmp(str, "EA", 3))
		cube->map->car = 3;
	else
		cube->map->car = -1;
	return (cube->map->car);
}

int	check_data_type(char *temp_line, int *valid_map, t_cube *cube)
{
	char	**data;
	char	*whitespaces;
	int		i;

	i = 0;
	if (is_whitespace_str(temp_line))
		return (0);
	whitespaces = whitespace_array();
	data = ft_split(temp_line, whitespaces);
	free(whitespaces);
	while (data[i])
	{
		if (is_cardinal(data[i], cube) > -1)
		{
			i++;
			if (check_cardinals(data[i], cube))
				return (1);
		}
		else if (data[i] && ft_strnstr(data[i], "F", 2))
		{
			i++;
			if (check_fc(&i, data, cube))
				return (1);
		}
		else if (data[i] && ft_strnstr(data[i], "C", 2))
		{
			i++;
			if (check_fc(&i, data, cube))
				return (1);
		}
		if (data[i])
			i++;
	}
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
		return(close(cube->map->fd), error_func("malloc"));
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
