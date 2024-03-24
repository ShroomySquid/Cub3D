/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:23:37 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 09:55:27 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int32_t	send_color(t_minimap *mini, mlx_image_t *img)
{
	int			y_img;
	int			x_img;
	int32_t		offset;

	y_img = (mini->y + mini->min_y) % 32;
	x_img = (mini->x + mini->min_x) % 32;
	offset = (x_img + (y_img * 32)) * 4;
	return (get_rgba(img->pixels[offset], img->pixels[offset + 1],
			img->pixels[offset + 2], img->pixels[offset + 3]));
}

int32_t	get_color_mini(t_minimap *mini, t_cube *c)
{
	mlx_image_t	*img;
	int			div_x;
	int			div_y;

	div_x = (mini->x + mini->min_x) / 32;
	div_y = (mini->y + mini->min_y) / 32;
	mini->coord = c->map->map[div_y][div_x];
	if (is_whitespace(mini->coord))
		return (get_rgba(32, 32, 32, 255));
	if (mini->coord == '1')
		img = c->wall_img;
	else if (mini->coord == 'D')
	{
		if (c->map->map[div_y][div_x - 1] == '1'
			&& c->map->map[div_y][div_x + 1] == '1')
			img = c->lockh_img;
		else if (c->map->map[div_y - 1][div_x] == '1'
			&& c->map->map[div_y + 1][div_x] == '1')
			img = c->lockv_img;
		else
			img = c->wall_img;
	}
	else
		img = c->floor_img;
	return (send_color(mini, img));
}
