/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/20 08:56:15 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	step(float *x, float *y, t_cube *c, float distance)
{
	*x += c->step_x * distance;
	*y += c->step_y * distance;
}

void	reverse_step(float *x, float *y, t_cube *c, float distance)
{
	*x -= c->step_x * distance;
	*y -= c->step_y * distance;
}

static int	ft_getside(float x, float y, t_cube *c)
{
	static int	last;
	float		last_x;
	float		last_y;
	int			coord[2];
	int			last_coord[2];

	last_x = x;
	last_y = y;
	coord[0] =  y / 32;
	coord[1] =  x / 32;
	if (c->map->map[coord[0]][coord[1]] == 'D')
	{
		if (c->map->map[coord[0]][coord[1] - 1] == '1' && c->map->map[coord[0]][coord[1] + 1] == '1')
		{
			if ((int)y % 32 == 19)
				return (0);
			if ((int)y % 32 == 13)
				return (1);
		}
		if (c->map->map[coord[0] - 1][coord[1]] == '1' && c->map->map[coord[0] + 1][coord[1]] == '1')
		{
			if ((int)x % 32 == 19)
				return (2);
			if ((int)x % 32 == 13)
				return (3);
		}
	}
	reverse_step(&last_x, &last_y, c, 0.1);
	last_coord[0] =  last_y / 32;
	last_coord[1] =  last_x / 32;
	if (coord[0] != last_coord[0] && coord[1] != last_coord[1])
		return (last);
	if (coord[0] == last_coord[0])
	{
		if (coord[1] > last_coord[1])
			last = 3;
		else
			last = 2;
	}
	else if (coord[0] < last_coord[0])
		last = 0;
	else
		last = 1;
	return (last);
}

static void	ft_send(t_scale *scale, t_cube *cube, float size)
{
	int	div_x;
	int	div_y;
	int	last_x;
	int	last_y;

	last_x = scale->x / 32;
	last_y = scale->y / 32;
	while (touch_wall(cube->map->map, 1, scale->x, scale->y))
		reverse_step(&scale->x, &scale->y, cube, size);
	if (!touch_wall(cube->map->map, 1, scale->x, scale->y))
		step(&scale->x, &scale->y, cube, size);
	while (!touch_wall(cube->map->map, 1, scale->x, scale->y))
	{
		div_x = scale->x / 32;
		div_y = scale->y / 32;
		if (div_x != last_x && div_y != last_y && cube->map->map[div_y][div_x] == '0')
		{
			if (last_x > div_x && last_y > div_y && cube->map->map[div_y + 1][div_x] == '1' && cube->map->map[div_y][div_x + 1] == '1' && cube->map->map[div_y + 1][div_x + 1] == '0')
			{
				reverse_step(&scale->x, &scale->y, cube, size);
				break ;
			}
			if (last_x < div_x && last_y > div_y && cube->map->map[div_y + 1][div_x] == '1' && cube->map->map[div_y][div_x - 1] == '1' && cube->map->map[div_y + 1][div_x - 1] == '0')
			{
				reverse_step(&scale->x, &scale->y, cube, size);
				break ;
			}
			if (last_x < div_x && last_y < div_y && cube->map->map[div_y - 1][div_x] == '1' && cube->map->map[div_y][div_x - 1] == '1' && cube->map->map[div_y - 1][div_x - 1] == '0')
			{
				reverse_step(&scale->x, &scale->y, cube, size);
				break ;
			}
			if (last_x > div_x && last_y < div_y && cube->map->map[div_y - 1][div_x] == '1' && cube->map->map[div_y][div_x + 1] == '1' && cube->map->map[div_y - 1][div_x + 1] == '0')
			{
				reverse_step(&scale->x, &scale->y, cube, size);
				break ;
			}
		}
		step(&scale->x, &scale->y, cube, size);
	}
	if (size > 0.01)
		ft_send(scale, cube, size / 2);
}

void	innit_scale(t_scale *scale, t_cube c, float screenx)
{
	scale->angle = c.rotation - c.precalc2;
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
	int				x_div;
	int				y_div;

	innit_scale(&scale, c, screenx);
	calculate_step(scale.angle, &c);
	ft_send(&scale, &c, 1);
	x_div = scale.x / SIZE;
	y_div = scale.y / SIZE;
	if (!c.draw_screen && c.map->map[y_div][x_div] == 'D' && !i[4] && !c.map->walls[(int)r[1]][i[4] + 1])
		return (0);
	r[1] = ft_getside(scale.x, scale.y, &c);
	if (!c.draw_screen && c.map->map[y_div][x_div] != 'D' && !i[(int)r[1]] && !c.map->walls[(int)r[1]][i[(int)r[1]] + 1])
		return (0);
	scale.hypo = hypotf(c.playery - scale.y, c.playerx - scale.x);
	scale.teta = (float)FOV / c.mlx->width * screenx - c.precalc2;
	scale.oppo = cosf(scale.teta * c.precalc) * scale.hypo;
	r[0] = SIZE * c.mlx->width / scale.oppo;
	if (c.map->map[y_div][x_div] != 'D')
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
	if (c.map->map[y_div][x_div] == 'D')
		r[1] = 4;
	return (r);
}

void	calculate_step(float rotation, t_cube *c)
{
	rotation = fmodf(rotation, 360) + (rotation < 0) * 360;
	if (rotation < 90)
	{
		c->step_y = -1 * cosf(rotation * c->precalc);
		c->step_x = sinf(rotation * c->precalc);
	}
	else if (rotation < 180)
	{
		rotation -= 90;
		c->step_x = cosf(rotation * c->precalc);
		c->step_y = sinf(rotation * c->precalc);
	}
	else if (rotation < 270)
	{
		rotation -= 180;
		c->step_y = cosf(rotation * c->precalc);
		c->step_x = -1 * sinf(rotation * c->precalc);
	}
	else
	{
		rotation -= 270;
		c->step_x = -1 * cosf(rotation * c->precalc);
		c->step_y = -1 * sinf(rotation * c->precalc);
	}
}
