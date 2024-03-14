/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/06 10:31:55 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int	ft_getside_loop(t_cube c, float r, float x, float y)
{
	float	o;

	o = 2;
	while (o / 2)
	{
		if ((r > 270 || r < 90) && touch_wall(c.map->map, 1, x + o, y)
			&& touch_wall(c.map->map, 1, x - o, y) && touch_wall(c.map->map, 1,
				x, y - o) && !touch_wall(c.map->map, 1, x, y + o))
			return (0);
		else if ((r > 180 && r < 360) && touch_wall(c.map->map, 1, x, y - o)
			&& touch_wall(c.map->map, 1, x, y + o) && touch_wall(c.map->map, 1,
				x - o, y) && !touch_wall(c.map->map, 1, x + o, y))
			return (2);
		else if ((r > 0 && r < 180) && touch_wall(c.map->map, 1, x, y - o)
			&& touch_wall(c.map->map, 1, x, y + o) && touch_wall(c.map->map, 1,
				x + o, y) && !touch_wall(c.map->map, 1, x - o, y))
			return (3);
		else if ((r > 90 && r < 270) && touch_wall(c.map->map, 1, x + o, y)
			&& touch_wall(c.map->map, 1, x - o, y) && touch_wall(c.map->map, 1,
				x, y + o) && !touch_wall(c.map->map, 1, x, y - o))
			return (1);
		o /= 2;
	}
	return (-1);
}

static int	ft_getside(t_cube cube, float x, float y, float rotation)
{
	static int	lastret;
	float		offset;
	int			ret;

	rotation = fmodf(rotation, 360) + (rotation < 0) * 360;
	offset = 2;
	ret = ft_getside_loop(cube, rotation, x, y);
	if (ret == -1)
		ret = lastret;
	lastret = ret;
	return (ret);
}

float	*ft_getscale(t_cube c, float screenx, int *i)
{
	static float	r[3];
	float			x;
	float			y;

	screenx = (screenx - c.mlx->width / 2.0) / c.mlx->width;
	x = c.playerx;
	y = c.playery;
	while (!touch_wall(c.map->map, 1, x, y))
		step(&x, &y, c.rotation + screenx * sqrt(c.mlx->width));
	r[1] = ft_getside(c, x, y, c.rotation + screenx * sqrt(c.mlx->width));
	r[0] = ((256 / hypot(fabs(c.playery - (int)y), fabs(c.playerx - (int)x))))
		* 256;
	if (!r[1])
		r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(x,
				32);
	else if (r[1] == 1)
		r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width
			- c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(x, 32);
	else if (r[1] == 2)
		r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width
			- c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(y, 32);
	else
		r[2] = c.map->walls[(int)r[1]][i[(int)r[1]]]->width / 32.0 * fmod(y,
				32);
	return (r);
}

int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	step(float *x, float *y, float rotation)
{
	rotation = fmodf(rotation, 360) + (rotation < 0) * 360;
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
