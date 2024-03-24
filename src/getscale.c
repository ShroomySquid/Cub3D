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
	scale->angle = c.rotation - c.precalc2;
	scale->angle += (float)FOV / c.mlx->width * screenx;
	if (scale->angle < 0)
		scale->angle += 360;
	else if (scale->angle >= 360)
		scale->angle -= 360;
	scale->size = 7;
	scale->x = c.playerx;
	scale->y = c.playery;
}

float	*getscale_next(t_cube c, int *i, t_scale scale, float *r)
{
	float	wall_width;

	r[0] = SIZE * c.mlx->width / scale.oppo;
	if (c.map->map[scale.y_div][scale.x_div] != 'D')
		wall_width = c.map->walls[(int)r[1]][i[(int)r[1]]]->width;
	else
		wall_width = c.map->walls[4][i[4]]->width;
	if (!r[1])
		r[2] = wall_width / SIZE * fmodf(scale.x, SIZE);
	else if (r[1] == 1)
		r[2] = wall_width - wall_width / SIZE * fmodf(scale.x, SIZE);
	else if (r[1] == 2)
		r[2] = wall_width - wall_width / SIZE * fmodf(scale.y, SIZE);
	else
		r[2] = wall_width / SIZE * fmodf(scale.y, SIZE);
	if (c.map->map[scale.y_div][scale.x_div] == 'D')
		r[1] = 4;
	return (r);
}

float	*ft_getscale(t_cube c, int screenx, int *i)
{
	float	*r;
	t_scale	scale;

	r = malloc(sizeof(float) * 4);
	if (!r)
		return (NULL);
	innit_scale(&scale, c, screenx);
	calculate_step(scale.angle, &c);
	ft_send(&scale, &c);
	scale.x_div = scale.x / SIZE;
	scale.y_div = scale.y / SIZE;
	r[1] = ft_getside(scale.x, scale.y, &c);
	if (!c.draw_screen && c.map->map[scale.y_div][scale.x_div] == 'D'
		&& !i[4] && !c.map->walls[(int)r[1]][i[4] + 1])
		return (free(r), NULL);
	if (!c.draw_screen && !i[(int)r[1]]
		&& !c.map->walls[(int)r[1]][i[(int)r[1]] + 1])
		return (free(r), NULL);
	scale.hypo = hypotf(c.playery - scale.y, c.playerx - scale.x);
	scale.teta = (float)FOV / c.mlx->width * screenx - c.precalc2;
	scale.oppo = cosf(scale.teta * c.precalc) * scale.hypo;
	r[0] = SIZE * c.mlx->width / scale.oppo;
	return (getscale_next(c, i, scale, r));
}
