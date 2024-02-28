/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2023/12/05 21:33:30 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	renderloop(mlx_t *mlx, char **map, t_cube *c)
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
			if (map[y][x] == '1' && i++)
				mlx_image_to_window(mlx, c->wall_img, x * 32, y * 32);
			if (ft_strchr("NSWE0", map[y][x]) && i++)
				mlx_image_to_window(mlx, c->floor_img, x * 32, y * 32);
			if (ft_strchr("NSWE", map[y][x]) && i++)
				mlx_image_to_window(mlx, c->player, x * 32, y * 32);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_set_instance_depth(&c->player->instances[0], i);
}

char	**render_map(t_cube *c)
{
	static int	i = 1;
	char		**map;
	t_list		*lst;

	lst = ft_lstnew(get_next_line(c->mapfd));
	while (ft_lstlast(lst)->content && i++)
		ft_lstadd_back(&lst, ft_lstnew(get_next_line(c->mapfd)));
	map = malloc((i + 1) * 8);
	i = 0;
	while (1 && lst->content)
	{
		map[i] = ft_strdup(lst->content);
		free(lst->content);
		free(lst);
		lst = lst->next;
		if (!map[i++])
			break ;
	}
	free(lst->content);
	free(lst);
	map[i] = 0;
	//checkmap(map, c);
	renderloop(c->mlx, map, c);
	return (map);
}
