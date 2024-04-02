/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getside.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:28:38 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/22 18:07:46 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	innit_scale(t_scale *scale, t_cube c, int screenx)
{
	scale->angle = c.rotation - c.half_fov;
	scale->angle += (float)FOV / c.mlx->width * screenx;
	if (scale->angle < 0)
		scale->angle += 360;
	else if (scale->angle >= 360)
		scale->angle -= 360;
	scale->size = 7;
	scale->x = c.playerx;
	scale->y = c.playery;
}

t_wall	getscale_next(t_cube c, int *i, t_scale scale, t_wall w)
{
	if (c.map->map[scale.y_div][scale.x_div] == 'D')
		w.img = c.map->walls[4][i[4]];
	else
		w.img = c.map->walls[w.side][i[w.side]];
	if (!w.side)
		w.x = (float)w.img->width / SIZE * fmodf(scale.x, SIZE);
	else if (w.side == 1)
		w.x = w.img->width - (float)w.img->width / SIZE * fmodf(scale.x, SIZE);
	else if (w.side == 2)
		w.x = w.img->width - (float)w.img->width / SIZE * fmodf(scale.y, SIZE);
	else
		w.x = (float)w.img->width / SIZE * fmodf(scale.y, SIZE);
	return (w);
}

t_wall	ft_getscale(t_cube c, int screenx, int *i)
{
	t_wall	w;
	t_scale	scale;

	innit_scale(&scale, c, screenx);
	calculate_step(scale.angle, &c);
	ft_send(&scale, &c);
	scale.x_div = scale.x / SIZE;
	scale.y_div = scale.y / SIZE;
	w.side = ft_getside(scale.x, scale.y, &c);
	if (!c.draw_screen && c.map->map[scale.y_div][scale.x_div] == 'D'
		&& !i[4] && !c.map->walls[4][i[4] + 1])
		return (w.draw = 0, w);
	if (!c.draw_screen && !i[w.side]
		&& !c.map->walls[w.side][i[w.side] + 1])
		return (w.draw = 0, w);
	scale.hypo = hypotf(c.playery - scale.y, c.playerx - scale.x);
	scale.teta = (float)FOV / c.mlx->width * screenx - c.half_fov;
	scale.oppo = cosf(scale.teta * c.radian) * scale.hypo;
	w.scale = SIZE * c.mlx->width / scale.oppo;
	w.draw = 1;
	return (getscale_next(c, i, scale, w));
}
