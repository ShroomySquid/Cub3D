/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:25:28 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 10:49:29 by fbarrett         ###   ########.fr       */
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

void	ft_image(t_cube *c)
{
	if (c->first)
		put_radicle(c);
	if (c->height_img != c->mlx->height || c->width_img != c->mlx->width)
	{
		c->height_div = c->mlx->height / 2;
		c->width_div = c->mlx->width / 2;
		c->draw_map = true;
		c->draw_player = true;
		c->draw_screen = true;
		c->height_img = c->mlx->height;
		c->width_img = c->mlx->width;
		if (!c->first)
			mlx_delete_image(c->mlx, c->render);
		c->render = mlx_new_image(c->mlx, c->mlx->width, c->mlx->height);
		c->pointer->instances[0].x = c->width_div - 16;
		c->pointer->instances[0].y = c->height_div - 16;
		mlx_image_to_window(c->mlx, c->render, 0, 0);
		mlx_set_instance_depth(&c->render->instances[0], 0);
	}
}

static int32_t	long_pixel(t_cube *cube, t_wall w, int y)
{
	return (get_pixel(w.img, w.x, w.img->height / w.scale * (y
				- (cube->mlx->height - w.scale) / 2)));
}

void	ft_render_loop(t_cube *cube, int x, int *i)
{
	float	val_div;
	t_wall	wall;
	int		y;

	wall = ft_getscale(*cube, x, i);
	if (!wall.draw)
		return ;
	val_div = wall.scale / 2.0;
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
			mlx_put_pixel(cube->render, x, y, long_pixel(cube, wall, y));
	}
}
