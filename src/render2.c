/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/17 17:09:47 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int	ft_getside(float x, float y, t_cube *c)
{
	static int	last;
	int			cur_x;
	int			cur_y;

	cur_x = (x / SIZE);
	cur_y = (y / SIZE);
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

static void	ft_send(float *x, float *y, float rotation, t_cube *cube)
{
	while (!touch_wall(cube->map->map, 1, *x, *y))
		step(x, y, rotation, cube, 1);
	while (touch_wall(cube->map->map, 1, *x, *y))
		step(x, y, rotation + 180, cube, 0.1);
	step(x, y, rotation, cube, 0.1);
	while (touch_wall(cube->map->map, 1, *x, *y))
		step(x, y, rotation + 180, cube, 0.01);
	step(x, y, rotation, cube, 0.01);
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
	int				wall_width;

	angle = c.rotation - FOV / 2.0 + (float)FOV / c.mlx->width * screenx;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	x = c.playerx;
	y = c.playery;
	ft_send(&x, &y, angle, &c);
	r[1] = ft_getside(x, y, &c);
	hypothenuse = hypot(c.playery - y, c.playerx - x);
	teta = -(FOV / 2.0) + (float)FOV / c.mlx->width * screenx;
	opposite = cos(fabs(teta) * (M_PI / 180)) * hypothenuse;
	r[0] = (float)SIZE * c.mlx->width / opposite;
	wall_width = c.map->walls[(int)r[1]][i[(int)r[1]]]->width;
	if (c.map->map[(int)y / SIZE][(int)x / SIZE] == 'D')
	{
		if (!r[1])
			r[2] = (float)c.map->walls[4][i[4]]->width / SIZE * fmod(x, SIZE);
		else if (r[1] == 1)
			r[2] = c.map->walls[4][i[4]]->width - (float)c.map->walls[4][i[4]]->width / SIZE * fmod(x, SIZE);
		else if (r[1] == 2)
			r[2] = c.map->walls[4][i[4]]->width - (float)c.map->walls[4][i[4]]->width / SIZE * fmod(y, SIZE);
		else
			r[2] = (float)c.map->walls[4][i[4]]->width / SIZE * fmod(y, SIZE);
		r[1] = 4;
	}
	else
	{
		if (!r[1])
			r[2] = wall_width / 32.0 * fmod(x, 32);
		else if (r[1] == 1)
			r[2] = wall_width - wall_width / 32.0 * fmod(x, 32);
		else if (r[1] == 2)
			r[2] = wall_width - wall_width / 32.0 * fmod(y, 32);
		else
			r[2] = wall_width / 32.0 * fmod(y, 32);
	}
	return (r);
}

int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	step(float *x, float *y, float rotation, t_cube *c, float distance)
{
	c->last_y = (int)(*y / SIZE);
	c->last_x = (int)(*x / SIZE);
	rotation = fmodf(rotation, 360) + (rotation < 0) * 360;
	if (rotation < 90.0)
	{
		*y -= distance / 90.0 * (90.0 - rotation);
		*x += distance / 90.0 * rotation;
	}
	else if (rotation < 180.0)
	{
		*y += (distance / 90.0 * rotation) - distance;
		*x += distance * 2 - (distance / 90.0 * rotation);
	}
	else if (rotation < 270.0)
	{
		*y += (distance / 90.0 * (90.0 - rotation - 180.0)) + 4 * distance;
		*x -= distance / 90.0 * (rotation - 180.0);
	}
	else
	{
		*y -= (distance / 90.0 * (rotation - 180.0)) - distance;
		*x -= 2 * distance - (distance / 90.0 * (rotation - 180.0));
	}
}
