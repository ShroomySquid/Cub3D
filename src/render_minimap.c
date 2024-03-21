/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/18 09:30:37 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int32_t	get_color_mini(t_minimap *mini, t_cube *c)
{
	int32_t		offset;
	int			y_img;
	int			x_img;
	mlx_image_t	*img;

	mini->coord = c->map->map[(mini->y + mini->min_y)
		/ 32][(mini->x + mini->min_x) / 32];
	if (is_whitespace(mini->coord))
		return (get_rgba(32, 32, 32, 255));
	if (mini->coord == '1')
		img = c->wall_img;
	else if (mini->coord == 'D')
	{
		if (c->map->map[(mini->y + mini->min_y) / 32][(mini->x + mini->min_x) / 32 - 1] == '1' && c->map->map[(mini->y + mini->min_y) / 32][(mini->x + mini->min_x) / 32 + 1] == '1')
			img = c->lockh_img;
		else if (c->map->map[(mini->y + mini->min_y) / 32 - 1][(mini->x + mini->min_x) / 32] == '1' && c->map->map[(mini->y + mini->min_y) / 32 + 1][(mini->x + mini->min_x) / 32] == '1')
			img = c->lockv_img;
		else
			img = c->wall_img;
	}
	else
		img = c->floor_img;
	y_img = (mini->y + mini->min_y) % 32;
	x_img = (mini->x + mini->min_x) % 32;
	offset = (x_img + (y_img * 32)) * 4;
	return (get_rgba(img->pixels[offset], img->pixels[offset + 1],
			img->pixels[offset + 2], img->pixels[offset + 3]));
}

int	get_last_x(int y, t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->map->map[y][i])
		i++;
	return (i);
}

int	is_outside_map(t_minimap mini, t_cube *c)
{
	if (mini.y + mini.min_y < 0 || (mini.y + mini.min_y) / 32 > c->last_line
		|| mini.x + mini.min_x < 0 || (mini.x + mini.min_x) / 32
		>= get_last_x((mini.y + mini.min_y) / 32, c))
	{
		return (1);
	}
	return (0);
}

void	innit_minimap(t_cube *c, t_minimap *mini)
{
	mini->min_x = c->playerx - 112;
	mini->min_y = c->playery - 112;
	mini->y = 0;
	mini->x = 0;
}

void	render_minimap(void *param)
{
	t_cube		*c;
	t_minimap	mini;

	c = param;
	if (c->samepos)
		return ;
	innit_minimap(c, &mini);
	while (mini.y < 224)
	{
		while (mini.x < 224)
		{
			if (is_mini_down(c))
				mlx_put_pixel(c->minimap_img, mini.x, mini.y,
					get_rgba(32, 32, 32, 0));
			else if (is_outside_map(mini, c))
				mlx_put_pixel(c->minimap_img, mini.x, mini.y,
					get_rgba(32, 32, 32, 255));
			else
				mlx_put_pixel(c->minimap_img, mini.x, mini.y,
					get_color_mini(&mini, c));
			mini.x += 1;
		}
		mini.y += 1;
		mini.x = 0;
	}
}
