/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/02/28 11:04:00 by lcouturi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int32_t get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	touch_tile(char **map, char c, int x, int y)
{
	return (map[y / 32][x / 32] == c);
}

static void	step(float *x, float *y, float rotation)
{
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
	float		xinit;
	float		y;
	float		yinit;

	screenx -= (float)HEIGHT / 2.0;
	x = cube->player->instances[0].x + screenx / 16.0;
	y = cube->player->instances[0].y;
	screenx /= 512.0;
	yinit = y;
	xinit = x;
	while (1)
	{
		step(&x, &y, (float)cube->rotation + screenx * 8.0);
		if (touch_tile(cube->map->map, '1', x, y))
		{
			if ((int)y % 32 == 31)
				ret[1] = get_rgba(0xFF, 0xFF, 0x00, 0xFF);
			else if ((int)x % 32 == 31)
				ret[1] = get_rgba(0xFF, 0x00, 0xFF, 0xFF);
			else
				ret[1] = get_rgba(0x00, 0xFF, 0xFF, 0xFF);
			break ;
		}
	}
	ret[0] = HEIGHT - 2.0 * sqrt(fabs(yinit - y) * fabs(yinit - y) + fabs(xinit - x) * fabs(xinit - x));
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
					mlx_put_pixel(cube->render, x, y, get_rgba(0xFF, 0x00, 0x00, 0xFF));
				else
					mlx_put_pixel(cube->render, x, y, get_rgba(0x00, 0x00, 0xFF, 0xFF));
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
