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

void	step(float *x, float *y, float rotation)
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
	static int	ret[3];
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
				ret[1] = 0;
			else if ((touch_wall(cube, x, y - 2.0) || touch_wall(cube, x, y
						+ 2.0)) && touch_wall(cube, x - 2.0, y)
				&& !touch_wall(cube, x + 2.0, y))
				ret[1] = 1;
			else if ((touch_wall(cube, x, y - 2.0) || touch_wall(cube, x, y
						+ 2.0)) && touch_wall(cube, x + 2.0, y)
				&& !touch_wall(cube, x - 2.0, y))
				ret[1] = 2;
			else
				ret[1] = 3;
			break ;
		}
	}
	ret[0] = (192 / hypotf(fabsf(cube->playery - y), fabsf(cube->playerx - x))) * 192;
	if (!ret[1])
		ret[2] = cube->map->NO->width / 32.0 * fmodf(x, 32);
	else if (ret[1] == 1)
		ret[2] = cube->map->WE->width - cube->map->WE->width / 32.0 * fmodf(y, 32);
	else if (ret[1] == 2)
		ret[2] = cube->map->EA->width / 32.0 * fmodf(y, 32);
	else
		ret[2] = cube->map->SO->width - cube->map->SO->width / 32.0 * fmodf(x, 32);
	return (ret);
}

int32_t	get_pixel(mlx_image_t *img, int x, int y)
{
	int32_t	offset;

	offset = (y * img->width + x) * 4;
	return (get_rgba(img->pixels[offset], img->pixels[offset + 1], img->pixels[offset + 2], img->pixels[offset + 3]));
}

void	ft_render(void *param)
{
	int			count;
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
		count = 0;
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
			{
				if (!val[1])
					mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->NO, val[2], (float)cube->map->NO->height / (float)val[0] * (float)count));
				else if (val[1] == 1)
					mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->WE, val[2], (float)cube->map->WE->height / (float)val[0] * (float)count));
				else if (val[1] == 2)
					mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->EA, val[2], (float)cube->map->EA->height / (float)val[0] * (float)count));
				else
					mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->SO, val[2], (float)cube->map->SO->height / (float)val[0] * (float)count));
				count++;
			}
		}
	}
	if (!done)
	{
		mlx_image_to_window(cube->mlx, cube->render, 0, 0);
		mlx_set_instance_depth(&cube->render->instances[0], 0);
		done = true;
	}
}
