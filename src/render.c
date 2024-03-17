/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/17 15:30:50 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static int32_t	get_pixel(mlx_image_t *img, int x, int y)
{
	const int32_t	offset = (y * img->width + x) * 4;

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

static void	ft_render_loop(t_cube *cube, float x, int *i)
{
	float	*val;
	float	y;

	y = -1;
	val = ft_getscale(*cube, x, i);
	while (++y < cube->mlx->height)
	{
		if (y < (float)cube->mlx->height / 2 - val[0] / 2
			|| y >= (float)cube->mlx->height / 2 + val[0] / 2)
		{
			if (y < cube->mlx->height / 2.0)
				mlx_put_pixel(cube->render, x, y, cube->map->roof);
			else
				mlx_put_pixel(cube->render, x, y, cube->map->floor);
		}
		else
			mlx_put_pixel(cube->render, x, y,
				get_pixel(cube->map->walls[(int)val[1]][i[(int)val[1]]], val[2],
					cube->map->walls[(int)val[1]][i[(int)val[1]]]->height
					/ val[0] * (y - (cube->mlx->height - val[0]) / 2)));
	}
}

void	ft_render(void *param)
{
	t_cube		*cube;
	// quossé i?
	static int	i[4];
	float		x;

	cube = param;
	ft_image(cube);
	x = -1;
	while (++x < cube->mlx->width)
		ft_render_loop(cube, x, i);
	i[0]++;
	if (!cube->map->walls[0][i[0]])
		i[0] = 0;
	i[1]++;
	if (!cube->map->walls[1][i[1]])
		i[1] = 0;
	i[2]++;
	if (!cube->map->walls[2][i[2]])
		i[2] = 0;
	i[3]++;
	if (!cube->map->walls[3][i[3]])
		i[3] = 0;
}
