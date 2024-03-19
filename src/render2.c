/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/18 16:16:30 by fbarrett         ###   ########.fr       */
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

static void	ft_send(t_scale *scale, t_cube *cube)
{
	while (!touch_wall(cube->map->map, 1, scale->x, scale->y))
		step(&scale->x, &scale->y, scale->angle, cube, 1);
	//while (touch_wall(cube->map->map, 1, scale->x, scale->y))
	//	step(&scale->x, &scale->y, scale->angle + 180, cube, 0.1);
	//step(&scale->x, &scale->y, scale->angle, cube, 0.1);
	//while (touch_wall(cube->map->map, 1, scale->x, scale->y))
	//	step(&scale->x, &scale->y, scale->angle + 180, cube, 0.01);
	//step(&scale->x, &scale->y, scale->angle, cube, 0.01);
}

void	innit_scale(t_scale *scale, t_cube c, float screenx)
{
	scale->angle = c.rotation - (FOV / 2.0);
	scale->angle += (float)FOV / c.mlx->width * screenx;
	if (scale->angle < 0)
		scale->angle += 360;
	else if (scale->angle >= 360)
		scale->angle -= 360;
	scale->x = c.playerx;
	scale->y = c.playery;
}

float	*ft_getscale(t_cube c, float screenx, int *i)
{
	static float	r[3];
	t_scale			scale;
	float			wall_width;

	innit_scale(&scale, c, screenx);
	ft_send(&scale, &c);
	r[1] = ft_getside(scale.x, scale.y, &c);
	scale.hypo = hypot(c.playery - scale.y, c.playerx - scale.x);
	scale.teta = (float)FOV / c.mlx->width * screenx - (FOV / 2.0);
	scale.oppo = cos(scale.teta * (M_PI / 180)) * scale.hypo;
	r[0] = (float)SIZE * c.mlx->width / scale.oppo;
	//r[0] = (float)SIZE * c.mlx->width / scale.hypo;
	wall_width = c.map->walls[(int)r[1]][i[(int)r[1]]]->width;
	if (c.map->map[(int)scale.y / SIZE][(int)scale.x / SIZE] == 'D')
		wall_width = c.map->walls[4][i[4]]->width;
	if (!r[1])
		r[2] = wall_width / SIZE * fmod(scale.x, SIZE);
	else if (r[1] == 1)
		r[2] = wall_width - wall_width / SIZE * fmod(scale.x, SIZE);
	else if (r[1] == 2)
		r[2] = wall_width - wall_width / SIZE * fmod(scale.y, SIZE);
	else
		r[2] = wall_width / SIZE * fmod(scale.y, SIZE);
	if (c.map->map[(int)scale.y / SIZE][(int)scale.x / SIZE] == 'D')
		r[1] = 4;
	return (r);
}

void	step(float *x, float *y, float rotation, t_cube *c, float distance)
{
	if (distance == 1)
	{
		c->last_y = (int)(*y / SIZE);
		c->last_x = (int)(*x / SIZE);
	}
	//printf("hello\n");
	rotation = fmodf(rotation, 360) + (rotation < 0) * 360;
	if (rotation == 90.0)
		*x += 1;
	else if (rotation == 0.0 || rotation == 360.0)
		*y -= 1;
	else if (rotation == 180.0)
		*y += 1;
	else if (rotation == 270.0)
		*x -= 1;
	else if (rotation < 90.0)
	{
		*y -= distance - (cos(rotation * (M_PI / 180)) * distance);
		*x += sin(rotation * (M_PI / 180)) * distance;
	}
	else if (rotation < 180.0)
	{
		rotation -= 90.0;
		*x += (cos(rotation * (M_PI / 180)) * distance);
		*y += distance - (sin(rotation * (M_PI / 180)) * distance);
	}
	else if (rotation < 270.0)
	{
		rotation -= 180.0;
		*y += distance - (cos(rotation * (M_PI / 180)) * distance);
		*x -= sin(rotation * (M_PI / 180)) * distance;
	}
	else
	{
		rotation -= 270.0;
		*x -= (cos(rotation * (M_PI / 180)) * distance);
		*y -= distance - (sin(rotation * (M_PI / 180)) * distance);
	}
}

/*
void	step(float *x, float *y, float rotation, t_cube *c, float distance)
{
	if (distance == 1)
	{
		c->last_y = (int)(*y / SIZE);
		c->last_x = (int)(*x / SIZE);
	}
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
*/
