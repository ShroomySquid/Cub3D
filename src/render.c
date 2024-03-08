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

static void	step(float *x, float *y, float rotation)
{
	rotation = fmodf(rotation, 360);
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

static float	*ft_getscale(t_cube *cube, float screenx)
{
	static float	ret[3];
	float			x;
	float			y;

	screenx -= (float)cube->mlx->width / 2;
	x = cube->playerx;
	y = cube->playery;
	screenx /= cube->mlx->width;
	while (!touch_wall(cube, x, y))
		step(&x, &y, cube->rotation + screenx * sqrtf(cube->mlx->width));
	if ((touch_wall(cube, x + 2, y) || touch_wall(cube, x - 2, y)) && touch_wall(cube, x, y - 2) && !touch_wall(cube, x, y + 2))
		ret[1] = 0;
	else if ((touch_wall(cube, x, y - 2) || touch_wall(cube, x, y + 2)) && touch_wall(cube, x - 2, y) && !touch_wall(cube, x + 2, y))
		ret[1] = 2;
	else if ((touch_wall(cube, x, y - 2) || touch_wall(cube, x, y + 2)) && touch_wall(cube, x + 2, y) && !touch_wall(cube, x - 2, y))
		ret[1] = 3;
	else
		ret[1] = 1;
	ret[0] = (192 / hypotf(fabsf(cube->playery - y), fabsf(cube->playerx - x))) * 384;
	if (!ret[1])
		ret[2] = (float)cube->map->NO->width / 32 * fmodf(x, 32);
	else if (ret[1] == 1)
		ret[2] = cube->map->SO->width - (float)cube->map->SO->width / 32 * fmodf(x, 32);
	else if (ret[1] == 2)
		ret[2] = cube->map->WE->width - (float)cube->map->WE->width / 32 * fmodf(y, 32);
	else
		ret[2] = (float)cube->map->EA->width / 32 * fmodf(y, 32);
	return (ret);
}

static int32_t	get_pixel(mlx_image_t *img, int x, int y)
{
	int32_t	offset;

	offset = (y * img->width + x) * 4;
	return (get_rgba(img->pixels[offset], img->pixels[offset + 1],
			img->pixels[offset + 2], img->pixels[offset + 3]));
}

static void	ft_image(t_cube *cube)
{
	static bool		exists;
	static int32_t	height;
	static int32_t	width;

	if (height != cube->mlx->height || width != cube->mlx->width)
	{
		height = cube->mlx->height;
		width = cube->mlx->width;
		if (exists)
			mlx_delete_image(cube->mlx, cube->render);
		else
			exists = true;
		cube->render = mlx_new_image(cube->mlx, cube->mlx->width,
				cube->mlx->height);
		mlx_image_to_window(cube->mlx, cube->render, 0, 0);
		mlx_set_instance_depth(&cube->render->instances[0], 0);
	}
}

void	ft_render(void *param)
{
	t_cube	*cube;
	float	*val;
	int		x;
	int		y;

	cube = param;
	ft_image(cube);
	x = -1;
	while (++x < cube->mlx->width)
	{
		y = -1;
		val = ft_getscale(cube, x);
		while (++y < cube->mlx->height)
		{
			if (y < (float)cube->mlx->height / 2 - val[0] / 2 || y >= (float)cube->mlx->height / 2 + val[0] / 2)
			{
				if (y < cube->mlx->height / 2)
					mlx_put_pixel(cube->render, x, y, cube->map->roof);
				else
					mlx_put_pixel(cube->render, x, y, cube->map->floor);
			}
			else if (!val[1])
				mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->NO, val[2], cube->map->NO->height / val[0] * (y - (cube->mlx->height - val[0]) / 2)));
			else if (val[1] == 1)
				mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->SO, val[2], cube->map->SO->height / val[0] * (y - (cube->mlx->height - val[0]) / 2)));
			else if (val[1] == 2)
				mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->WE, val[2], cube->map->WE->height / val[0] * (y - (cube->mlx->height - val[0]) / 2)));
			else
				mlx_put_pixel(cube->render, x, y, get_pixel(cube->map->EA, val[2], cube->map->EA->height / val[0] * (y - (cube->mlx->height - val[0]) / 2)));
		}
	}
}
