/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/19 10:37:35 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static mlx_image_t	*load_img(t_cube *c, char *str)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
		return (error_func("mlx_load_png"), NULL);
	img = mlx_texture_to_image(c->mlx, texture);
	if (!img)
		return (error_func("mlx_texture_to_image"), NULL);
	mlx_delete_texture(texture);
	return (img);
}

int	check_each_path(char **split_path, t_cube *c, int *i)
{
	if (!split_path[*i])
		return (error_map("No texture file for element"));
	while (split_path[*i])
	{
		c->map->walls[c->map->car][*i] = load_img(c, split_path[*i]);
		if (!c->map->walls[c->map->car][*i])
			return (1);
		*i += 1;
	}
	c->map->walls[c->map->car][*i] = 0;
	c->map->grey_brick_1 = load_img(c, "png/grey_brick_1.png");
	if (!c->map->grey_brick_1)
		return (1);
	return (0);
}

int	check_cardinals(char *paths, t_cube *c)
{
	int		i;
	char	**split_path;

	i = 0;
	if (c->map->walls[c->map->car])
		return (error_map("Multiple textures files for same element"));
	split_path = ft_split(paths, ";");
	if (!split_path)
		return (error_func("ft_split"));
	c->map->walls[c->map->car] = malloc((array_len(split_path) + 1)
			* sizeof(mlx_image_t *));
	if (!c->map->walls[c->map->car])
		return (free_all(split_path), error_func("malloc"));
	if (check_each_path(split_path, c, &i))
		return (free_all(split_path), 1);
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
	else if (!ft_strncmp(str, "DO", 3))
		cube->map->car = 4;
	else
		cube->map->car = -1;
	return (cube->map->car);
}
