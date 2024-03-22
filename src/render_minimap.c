/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:34:09 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/22 19:23:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
	const int	div_y = (mini.y + mini.min_y) / 32;

	if (mini.y + mini.min_y < 0 || div_y > c->last_line
		|| mini.x + mini.min_x < 0 || (mini.x + mini.min_x) / 32
		>= get_last_x(div_y, c))
		return (1);
	return (0);
}

static int	innit_minimap(t_cube *c, t_minimap *mini)
{
	if (!c->draw_map)
		return (1);
	mini->min_x = c->playerx - 112;
	mini->min_y = c->playery - 112;
	mini->y = 0;
	return (0);
}

void	render_minimap(void *param)
{
	t_cube		*c;
	t_minimap	mini;

	c = param;
	if (innit_minimap(c, &mini))
		return ;
	while (mini.y < 224)
	{
		mini.x = 0;
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
	}
	c->draw_map = false;
}
