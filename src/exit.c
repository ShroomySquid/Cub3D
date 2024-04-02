/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:13:43 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/31 15:47:18 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

static void	free_walls(mlx_image_t ***array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	force_exit(t_cube *cube)
{
	if (!cube)
		return (1);
	if (cube->floor_tex)
		mlx_delete_texture(cube->floor_tex);
	if (cube->wall_tex)
		mlx_delete_texture(cube->wall_tex);
	if (cube->lockh_tex)
		mlx_delete_texture(cube->lockh_tex);
	if (cube->lockv_tex)
		mlx_delete_texture(cube->lockv_tex);
	if (cube->pointer_tex)
		mlx_delete_texture(cube->pointer_tex);
	if (cube->map && cube->map->walls)
		free_walls(cube->map->walls);
	if (cube->map && cube->map->map)
		free_all(cube->map->map);
	if (cube->map)
		free(cube->map);
	mlx_terminate(cube->mlx);
	free(cube);
	return (1);
}
