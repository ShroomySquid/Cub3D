/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/11 17:15:51 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int32_t get_color_mini(int x, int y, t_cube *c, char coord)
{	
	int32_t 	offset;
	int			y_img;
	int			x_img;
	mlx_image_t	*img;

	if (coord == '1')
		img = c->wall_img;
	else
		img = c->floor_img;
	y_img = y % 32;
	x_img = x % 32;
	offset = (x_img + (y_img * 32)) * 4;
	return (get_rgba(img->pixels[offset], img->pixels[offset + 1], img->pixels[offset + 2], img->pixels[offset + 3]));
}

int	get_last_x(int y, t_cube *cube)
{
	int i;

	i = 0;
	while (cube->map->map[y][i])
		i++;
	return (i);
}

void	render_minimap(void *param)
{
	t_cube	*c;
	int		y;
	int		x;
	char	coord;

	c = param;
	c->mini->min_x = c->playerx - 112;
	c->mini->min_y = c->playery - 112;
	y = 0;
	x = 0;
	while (y < 224)
	{
		while (x < 224)
		{
			if (y + c->mini->min_y < 0 || (y + c->mini->min_y) / 32
					> c->mini->last_line
					|| x + c->mini->min_x < 0 || (x + c->mini->min_x) / 32
					>= get_last_x((y + c->mini->min_y) / 32, c))
			{
				mlx_put_pixel(c->minimap_img, x, y, get_rgba(255,255,255,0));
				x++;
				continue ;
			}
			coord = c->map->map[(y + c->mini->min_y) / 32][(x + c->mini->min_x) / 32];
			if (is_whitespace(coord))
				mlx_put_pixel(c->minimap_img, x, y, get_rgba(255,255,255,0));
			else
				mlx_put_pixel(c->minimap_img, x, y, get_color_mini(x, y, c, coord));
			x++;
		}
		y++;
		x = 0;
	}
}
