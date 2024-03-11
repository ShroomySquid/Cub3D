/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/11 17:39:03 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	render_player(void *param)
{
	t_cube *cube;
	uint32_t	x;
	uint32_t	y;

	cube = param;
	x = 0;
	y = 0;
	while (x < cube->player->width)
	{
		while (y < cube->player->height)
		{
			if (y > 12 && y < 18 && x > 12 && x < 18)
				mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 255));
			y++;
		}
		y = 0;
		x++;
	}
}
