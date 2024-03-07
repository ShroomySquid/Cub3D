/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/07 10:21:40 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	render_minimap(mlx_t *mlx, char **map, t_cube *c)
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
