/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:25:28 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 10:26:37 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int32_t	get_pixel(mlx_image_t *img, int x, int y)
{
	const int32_t	offset = (y * img->width + x) * 4;

	return (get_rgba(img->pixels[offset], img->pixels[offset + 1],
			img->pixels[offset + 2], img->pixels[offset + 3]));
}

void	put_radicle(t_cube *cube)
{
	cube->pointer_tex = mlx_load_png("./png/radicle.png");
	cube->pointer = mlx_texture_to_image(cube->mlx, cube->pointer_tex);
	mlx_image_to_window(cube->mlx, cube->pointer, cube->width_div - 16,
		cube->height_div - 16);
	cube->first = false;
}

void	ft_image(t_cube *cube)
{
	static int32_t	height;
	static int32_t	width;

	if (cube->first)
		put_radicle(cube);
	if (height != cube->mlx->height || width != cube->mlx->width)
	{
		cube->height_div = cube->mlx->height / 2;
		cube->width_div = cube->mlx->width / 2;
		cube->draw_map = true;
		cube->draw_player = true;
		cube->draw_screen = true;
		height = cube->mlx->height;
		width = cube->mlx->width;
		if (!cube->first)
			mlx_delete_image(cube->mlx, cube->render);
		cube->render = mlx_new_image(cube->mlx, cube->mlx->width,
				cube->mlx->height);
		cube->pointer->instances[0].x = cube->width_div - 16;
		cube->pointer->instances[0].y = cube->height_div - 16;
		mlx_image_to_window(cube->mlx, cube->render, 0, 0);
		mlx_set_instance_depth(&cube->render->instances[0], 0);
	}
}

void	ft_render_loop(t_cube *cube, int x, int *i)
{
	float	*val;
	float	val_div;
	int		y;

	val = ft_getscale(*cube, x, i);
	if (!val)
		return ;
	val_div = val[0] / 2;
	y = -1;
	while (++y < cube->mlx->height)
	{
		if (y < cube->height_div - val_div || y >= cube->height_div + val_div)
		{
			if (!cube->draw_screen)
				continue ;
			else if (y < cube->height_div)
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
	free(val);
}
