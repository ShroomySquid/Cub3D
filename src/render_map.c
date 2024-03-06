/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/06 11:26:41 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	renderloop(mlx_t *mlx, char **map, t_cube *c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				i++;
				mlx_image_to_window(mlx, c->wall_img, x * 32, y * 32);
			}
			if (ft_strchr("NSWE0", map[y][x]))
			{
				i++;
				mlx_image_to_window(mlx, c->floor_img, x * 32, y * 32);
			}
			if (ft_strchr("NSWE", map[y][x]))
			{
				i++;
				mlx_image_to_window(mlx, c->player, (x * 32) + 5, (y * 32) + 5);
			}
			x++;
		}
		y++;
		x = 0;
	}
	mlx_set_instance_depth(&c->player->instances[0], i - 1);
}

int	count_lines(char *str)
{
	int i;
	int new_lines;

	i = 0;
	new_lines = 0;
	if (!str)
		return (new_lines);
	while (str[i])
	{
		if (str[i] == '\n')
			new_lines += 1;
		i++;
	}
	return (new_lines);
}

int	check_map_len(t_cube *cube, char **argv)
{
	int		map_len;
	int		read_ret_val;
	char	*buff;
	int		buff_size;

	buff_size = 100000;
	map_len = 0;
	buff = malloc(buff_size + 1);
	if (!buff)
		return (error_func("malloc"), -1);
	cube->map->fd = open(argv[1], O_RDONLY);
	if (cube->map->fd == -1)
		return (error_map("Failed to open map file"), -1);
	read_ret_val = read(cube->map->fd, buff, buff_size);
	while (read_ret_val == buff_size)
	{
		buff[read_ret_val] = 0;
		map_len += count_lines(buff);	
		read_ret_val = read(cube->map->fd, buff, buff_size);
	}
	map_len += count_lines(buff);
	free(buff);
	close(cube->map->fd);
	if (map_len == 0)
		return (error_map("Map is empty"), -1);
	return (map_len);
}

int	check_extension(char **argv)
{
	int i;
	
	i = 0;
	while (argv[1][i])
		i++;
	i -= 4;
	if (i <= 0)
		return (1);
	if (!ft_strnstr(&argv[1][i], ".cub", 4))
		return (1);
	return (0);
}

char	**render_map(t_cube *c, char **argv)
{
	int			i;
	char		**map;

	if (check_extension(argv))
		return (error_map("Invalid extension"), NULL); 
	c->map->nbr_line = check_map_len(c, argv);
	i = 0;
	if (c->map->nbr_line == -1)
		return (NULL);
	c->map->fd = open(argv[1], O_RDONLY);
	if (c->map->fd == -1)
		return (error_map("Failed to open map file"), NULL);
	if (check_textures(c))
		return (NULL); 
	map = malloc((c->map->nbr_line + 1) * sizeof(char*));
	if (!map)
		return (error_func("malloc"), close(c->map->fd), NULL);
	while (i < c->map->nbr_line)
	{
		map[i] = get_next_line(c->map->fd);
		printf("map: %s\n", map[i]);
		if (!map[i])
			return (error_func("GNL"), close(c->map->fd), free_all(map), NULL);
		i++;
	}
	map[i] = 0;
	close(c->map->fd);
	return (map);
}
