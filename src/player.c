/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 08:18:38 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 08:18:40 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	put_player(uint32_t x, uint32_t y, t_cube *c)
{
	while (x < c->player->width)
	{
		while (y < c->player->height)
		{
			if (!is_mini_down(c) && y > 109 && y < 115 && x > 109 && x < 115)
				mlx_put_pixel(c->player, x, y, get_rgba(255, 255, 255, 255));
			else
				mlx_put_pixel(c->player, x, y, get_rgba(255, 255, 255, 0));
			y++;
		}
		y = 0;
		x++;
	}
}

void	render_player(void *param)
{
	t_cube		*cube;
	uint32_t	x;
	uint32_t	y;
	int			los;

	cube = param;
	if (!cube->draw_player)
		return ;
	los = cube->rotation - (FOV / 2.0);
	if (los < 0)
		los += 360;
	x = 0;
	y = 0;
	put_player(x, y, cube);
	if (cube->is_light_active)
		draw_los(los, cube);
	cube->draw_player = false;
}
