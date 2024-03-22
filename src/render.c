/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcouturi <lcouturi@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by lcouturi          #+#    #+#             */
/*   Updated: 2024/03/22 16:43:31 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
	t_cube			*cube;
	static float	i[5];
	int				j[5];
	int				x;

	j[0] = i[0];
	j[1] = i[1];
	j[2] = i[2];
	j[3] = i[3];
	j[4] = i[4];
	cube = param;
	ft_framerate(cube);
	ft_image(cube);
	x = -1;
	while (++x < cube->mlx->width)
		ft_render_loop(cube, x, j);
	ft_animloop(i, cube);
	cube->draw_screen = false;
}
