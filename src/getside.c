/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getside.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:28:38 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/22 17:36:16 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int	is_door(t_cube *c, int *coord, float y, float x)
{
	if (c->map->map[coord[0]][coord[1] - 1] == '1'
		&& c->map->map[coord[0]][coord[1] + 1] == '1')
	{
		if ((int)y % 32 == 19)
			return (0);
		if ((int)y % 32 == 13)
			return (1);
	}
	if (c->map->map[coord[0] - 1][coord[1]] == '1' && c->map->map[coord[0]
		+ 1][coord[1]] == '1')
	{
		if ((int)x % 32 == 19)
			return (2);
		if ((int)x % 32 == 13)
			return (3);
	}
	return (-1);
}

int	innit_getside(float x, float y, t_cube *c, t_side *s)
{
	s->last_x = x;
	s->last_y = y;
	s->coord[0] = y / 32;
	s->coord[1] = x / 32;
	if (c->map->map[s->coord[0]][s->coord[1]] == 'D' && is_door(c, s->coord, y,
			x) != -1)
		return (is_door(c, s->coord, y, x));
	reverse_step(&s->last_x, &s->last_y, c, 0.1);
	s->last_coord[0] = s->last_y / 32;
	s->last_coord[1] = s->last_x / 32;
	return (-1);
}

int	ft_getside(float x, float y, t_cube *c)
{
	static int	last;
	int			temp;
	t_side		s;

	temp = innit_getside(x, y, c, &s);
	if (temp != -1)
	{
		last = temp;
		return (last);
	}
	if (s.coord[0] != s.last_coord[0] && s.coord[1] != s.last_coord[1])
		return (last);
	if (s.coord[0] == s.last_coord[0])
	{
		if (s.coord[1] > s.last_coord[1])
			last = 3;
		else
			last = 2;
	}
	else if (s.coord[0] < s.last_coord[0])
		last = 0;
	else
		last = 1;
	return (last);
}
