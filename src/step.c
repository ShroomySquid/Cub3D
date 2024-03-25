/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/22 16:48:49 by fbarrett         ###   ########.fr       */
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

static int	check_corners(t_scale *scale, t_cube *cube, int last_x, int last_y)
{
	int	div_x;
	int	div_y;

	div_x = scale->x / 32;
	div_y = scale->y / 32;
	if (div_x != last_x && div_y != last_y)
	{
		if (last_x > div_x && last_y > div_y
			&& (ft_strchr("1D", cube->map->map[div_y + 1][div_x])
			|| ft_strchr("1D", cube->map->map[div_y][div_x + 1])))
			return (reverse_step(&scale->x, &scale->y, cube, scale->size), 1);
		if (last_x < div_x && last_y > div_y
			&& (ft_strchr("1D", cube->map->map[div_y + 1][div_x])
			|| ft_strchr("1D", cube->map->map[div_y][div_x - 1])))
			return (reverse_step(&scale->x, &scale->y, cube, scale->size), 1);
		if (last_x < div_x && last_y < div_y
			&& (ft_strchr("1D", cube->map->map[div_y - 1][div_x])
			|| ft_strchr("1D", cube->map->map[div_y][div_x - 1])))
			return (reverse_step(&scale->x, &scale->y, cube, scale->size), 1);
		if (last_x > div_x && last_y < div_y
			&& (ft_strchr("1D", cube->map->map[div_y - 1][div_x])
			|| ft_strchr("1D", cube->map->map[div_y][div_x + 1])))
			return (reverse_step(&scale->x, &scale->y, cube, scale->size), 1);
	}
	return (step(&scale->x, &scale->y, cube, scale->size), 0);
}

void	ft_send(t_scale *scale, t_cube *cube)
{
	int	last_x;
	int	last_y;

	last_x = scale->x / 32;
	last_y = scale->y / 32;
	while (touch_wall(cube->map->map, 1, scale->x, scale->y))
		reverse_step(&scale->x, &scale->y, cube, scale->size);
	if (!touch_wall(cube->map->map, 1, scale->x, scale->y))
		step(&scale->x, &scale->y, cube, scale->size);
	while (!touch_wall(cube->map->map, 1, scale->x, scale->y))
		if (check_corners(scale, cube, last_x, last_y))
			break ;
	if (scale->size > 0.01)
	{
		scale->size /= 2;
		ft_send(scale, cube);
	}
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
