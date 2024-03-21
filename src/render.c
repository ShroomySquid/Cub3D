/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/18 13:36:50 by fbarrett         ###   ########.fr       */
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
	static bool		first = true;
	static int32_t	height;
	static int32_t	width;

	if (first)
	{
		cube->pointer_tex = mlx_load_png("./png/radicle.png");
		cube->pointer = mlx_texture_to_image(cube->mlx, cube->pointer_tex);
		mlx_image_to_window(cube->mlx, cube->pointer, cube->mlx->width / 2 - 16,
			cube->mlx->height / 2 - 16);
	}
	if (height != cube->mlx->height || width != cube->mlx->width)
	{
		cube->samepos = 2;
		height = cube->mlx->height;
		width = cube->mlx->width;
		if (!first)
			mlx_delete_image(cube->mlx, cube->render);
		cube->render = mlx_new_image(cube->mlx, cube->mlx->width,
				cube->mlx->height);
		cube->pointer->instances[0].x = cube->mlx->width / 2 - 16;
		cube->pointer->instances[0].y = cube->mlx->height / 2 - 16;
		mlx_image_to_window(cube->mlx, cube->render, 0, 0);
		mlx_set_instance_depth(&cube->render->instances[0], 0);
	}
	first = false;
}

static void	ft_render_loop(t_cube *cube, float x, int *i)
{
	float	*val;
	float	y;

	val = ft_getscale(*cube, x, i);
	if (!val)
		return ;
	y = -1;
	while (++y < cube->mlx->height)
	{
		if (y < (float)cube->mlx->height / 2 - val[0] / 2
			|| y >= (float)cube->mlx->height / 2 + val[0] / 2)
		{
			if (cube->samepos)
				continue ;
			else if (y < cube->mlx->height / 2.0)
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

static int	len(mlx_image_t **img)
{
	int	i;

	i = 0;
	while (img[i])
		i++;
	return (i);
}

static void	ft_framerate(t_cube *cube)
{
	static mlx_image_t	*counter;
	char				*str;
	char				*str2;

	str = ft_itoa(1 / cube->mlx->delta_time);
	str2 = ft_strjoin(str, "fps");
	free(str);
	if (counter)
		mlx_delete_image(cube->mlx, counter);
	counter = mlx_put_string(cube->mlx, str2, 0, 0);
	free(str2);
}

static void	ft_animloop(float *i, t_cube *cube)
{
	i[0] += cube->mlx->delta_time * 60;
	if (!cube->map->walls[0][(int)i[0]])
		i[0] = 0;
	i[0] = fmodf(i[0], len(cube->map->walls[0]));
	i[1] += cube->mlx->delta_time * 60;
	if (!cube->map->walls[1][(int)i[1]])
		i[1] = 0;
	i[1] = fmodf(i[1], len(cube->map->walls[1]));
	i[2] += cube->mlx->delta_time * 60;
	if (!cube->map->walls[2][(int)i[2]])
		i[2] = 0;
	i[2] = fmodf(i[2], len(cube->map->walls[2]));
	i[3] += cube->mlx->delta_time * 60;
	if (!cube->map->walls[3][(int)i[3]])
		i[3] = 0;
	i[3] = fmodf(i[3], len(cube->map->walls[3]));
	i[4] += cube->mlx->delta_time * 60;
	if (!cube->map->walls[4][(int)i[4]])
		i[4] = 0;
	i[4] = fmodf(i[4], len(cube->map->walls[4]));
}

void	ft_render(void *param)
{
	static float	protation;
	static float	px;
	static float	py;
	t_cube			*cube;
	static float	i[5];
	int				j[5];
	float			x;

	j[0] = i[0];
	j[1] = i[1];
	j[2] = i[2];
	j[3] = i[3];
	j[4] = i[4];
	cube = param;
	ft_framerate(cube);
	cube->samepos = (protation == cube->rotation && px == cube->playerx && py == cube->playery && cube->samepos != 2);
	ft_image(cube);
	x = -1;
	while (++x < cube->mlx->width)
		ft_render_loop(cube, x, j);
	protation = cube->rotation;
	px = cube->playerx;
	py = cube->playery;
	ft_animloop(i, cube);
}
