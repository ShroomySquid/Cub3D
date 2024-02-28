/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/02/28 15:45:46 by fbarrett         ###   ########.fr       */
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
			if (ft_strchr("NSWE0", map[y][x]) && i++)
				mlx_image_to_window(mlx, c->floor_img, x * 32, y * 32);
			if (ft_strchr("NSWE", map[y][x]) && i++)
				mlx_image_to_window(mlx, c->player, x * 32, y * 32);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_set_instance_depth(&c->player->instances[0], i - 1);
}

char	**render_map(t_cube *c, char **argv)
{
	int			i;
	char		**map;
	t_list		*lst;
	t_list		*temp_lst;

	i = 0;
	c->map = open(argv[1], O_RDONLY);
	if (c->map == -1)
		return (error_map("Failed to open map file"), NULL);
	lst = ft_lstnew(get_next_line(c->map));
	while (ft_lstlast(lst)->content)
	{
		ft_lstadd_back(&lst, ft_lstnew(get_next_line(c->map)));
		i++;
	}
	map = ft_calloc((i + 1), sizeof(char));
	if (!map)
		return (error_func("ft_calloc"), close(c->map), ft_lstclear(&lst, free), NULL);
	i = 0;
	while (lst->content)
	{
		map[i] = ft_strdup(lst->content);
		printf("%s", map[i]);
		if (!map[i])
			return (error_func("ft_strdup"), close(c->map), ft_lstclear(&lst, free), NULL);
		free(lst->content);
		temp_lst = lst->next;
		free(lst);
		lst = temp_lst;
		i++;
	}
	map[i] = 0;
	close(c->map);
	return (map);
}
