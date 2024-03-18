/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/18 10:00:15 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	is_mini_down(t_cube *c)
{
	if (!c->is_mini_active)
		return (1);
	return (0);
}

int	set_minimap(t_cube *cube)
{
	cube->player = mlx_new_image(cube->mlx, 64, 64);
	if (!cube->player)
		return (error_func("mlx_new_image"));
	cube->minimap_img = mlx_new_image(cube->mlx, 224, 224);
	if (!cube->minimap_img)
		return (error_func("mlx_new_image"));
	cube->lock_tex = mlx_load_png("./png/lock.png");
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	cube->lock_img = mlx_texture_to_image(cube->mlx, cube->lock_tex);
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	mlx_image_to_window(cube->mlx, cube->minimap_img, 20, 20);
	mlx_image_to_window(cube->mlx, cube->player, 100, 101);
	mlx_set_instance_depth(&cube->minimap_img->instances[0], 1);
	mlx_set_instance_depth(&cube->player->instances[0], 2);
	return (0);
}
