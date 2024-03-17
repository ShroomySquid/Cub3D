/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/17 15:47:42 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int	ft_getside(float x, float y, t_cube *c)
{
	static int	last;
	int			cur_x;
	int			cur_y;

	cur_x = (x / 32);
	cur_y = (y / 32);
	if (cur_y != c->last_y && cur_x != c->last_x)
		return (last);
	if (cur_y == c->last_y)
	{
		if (cur_x > c->last_x)
			last = 3;
		else
			last = 2;
	}
	else if (cur_y < c->last_y)
		last = 0;
	else
		last = 1;
	return (last);
}

float	*ft_getscale(t_cube c, float screenx, int *i)
{
	float			angle;
	float			hypothenuse;
	float			opposite;
	float			teta;
	static float	r[3];
	float			x;
	float			y;

	angle = c.rotation - FOV / 2.0 + (float)FOV / c.mlx->width * screenx;
	angle = fmodf(angle, 360) + (angle < 0) * 360;
	x = c.playerx;
	y = c.playery;
	while (!touch_wall(c.map->map, 1, x, y))
		step(&x, &y, angle, &c);
	r[1] = ft_getside(x, y, &c);
	hypothenuse = hypot(fabs((c.playery - (int)y)), fabs(c.playerx - (int)x));
	teta = -(FOV / 2.0) + (float)FOV / c.mlx->width * screenx;
	opposite = cos(teta * (M_PI / 180)) * hypothenuse;
	r[0] = 32768 / opposite;
	if (c.map->map[(int)y / 32][(int)x / 32] == 'D')
	{
		if (!r[1])
			r[2] = c.map->walls[4][i[4]]->width / 32.0 * fmod(x, 32);
		else if (r[1] == 1)
			r[2] = c.map->walls[4][i[4]]->width - c.map->walls[(int)r[1]][i[4]]->width / 32.0 * fmod(x, 32);
		else if (r[1] == 2)
			r[2] = c.map->walls[4][i[4]]->width - c.map->walls[(int)r[1]][i[4]]->width / 32.0 * fmod(y, 32);
		else
			r[2] = c.map->walls[4][i[4]]->width / 32.0 * fmod(y, 32);
		r[1] = 4;
	}
	else
	{
		if (!r[1])
			r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(x, 32);
		else if (r[1] == 1)
			r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width - c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(x, 32);
		else if (r[1] == 2)
			r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width - c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(y, 32);
		else
			r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(y, 32);
	}
	return (r);
}

int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	step(float *x, float *y, float rotation, t_cube *c)
{
	c->last_y = (int)(*y / 32);
	c->last_x = (int)(*x / 32);
	if (rotation < 90.0)
	{
		*y -= 1.0 / 90.0 * (90.0 - rotation);
		*x += 1.0 / 90.0 * rotation;
	}
	else if (rotation < 180.0)
	{
		*y += (1.0 / 90.0 * rotation) - 1.0;
		*x += 2.0 - (1.0 / 90.0 * rotation);
	}
	else if (rotation < 270.0)
	{
		*y += (1.0 / 90.0 * (90.0 - rotation - 180.0)) + 4.0;
		*x -= 1.0 / 90.0 * (rotation - 180.0);
	}
	else
	{
		*y -= (1.0 / 90.0 * (rotation - 180.0)) - 1.0;
		*x -= 2.0 - (1.0 / 90.0 * (rotation - 180.0));
	}
}
