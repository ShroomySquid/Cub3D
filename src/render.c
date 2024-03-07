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

int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	touch_wall(t_cube *cube, int x, int y)
{
	return (cube->map->map[y / 32][x / 32] == '1');
}

static void	step(float *x, float *y, float rotation)
{
	rotation = fmod(rotation, 360);
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

static int	*ft_getscale(t_cube *cube, float screenx)
{
	static int	ret[2];
	float		x;
	float		y;

	screenx -= (float)HEIGHT / 2.0;
	x = cube->playerx;
	y = cube->playery;
	screenx /= 512.0;
	while (1)
	{
		step(&x, &y, (float)cube->rotation + screenx * 16.0);
		if (touch_wall(cube, x, y))
		{
			if ((touch_wall(cube, x + 2.0, y) || touch_wall(cube, x - 2.0, y))
				&& touch_wall(cube, x, y - 2.0) && !touch_wall(cube, x, y
					+ 2.0))
				ret[1] = get_rgba(0xFF, 0xFF, 0x00, 0xFF);
			else if ((touch_wall(cube, x, y - 2.0) || touch_wall(cube, x, y
						+ 2.0)) && touch_wall(cube, x - 2.0, y)
				&& !touch_wall(cube, x + 2.0, y))
				ret[1] = get_rgba(0xFF, 0x00, 0xFF, 0xFF);
			else if ((touch_wall(cube, x, y - 2.0) || touch_wall(cube, x, y
						+ 2.0)) && touch_wall(cube, x + 2.0, y)
				&& !touch_wall(cube, x - 2.0, y))
				ret[1] = get_rgba(0x00, 0xFF, 0xFF, 0xFF);
			else
				ret[1] = get_rgba(0x80, 0x80, 0x00, 0xFF);
			break ;
		}
	}
	ret[0] = (256 / hypotf(fabsf(cube->playery - y), fabsf(cube->playerx - x)))
		* 256;
	return (ret);
}

void	ft_render(void *param)
{
	t_cube		*cube;
	static bool	done = false;
	int			*val;
	int			x;
	int			y;

	cube = param;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		val = ft_getscale(cube, (float)x);
		while (++y < HEIGHT)
		{
			if (y < HEIGHT / 2 - val[0] / 2 || y >= HEIGHT / 2 + val[0] / 2)
			{
				if (y < HEIGHT / 2)
					mlx_put_pixel(cube->render, x, y, cube->map->roof);
				else
					mlx_put_pixel(cube->render, x, y, cube->map->floor);
			}
			else
				mlx_put_pixel(cube->render, x, y, val[1]);
		}
	}
	if (!done)
	{
		mlx_image_to_window(cube->mlx, cube->render, 0, 0);
		mlx_set_instance_depth(&cube->render->instances[0], 0);
		done = true;
	}
}
