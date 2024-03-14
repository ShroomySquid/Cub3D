/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/14 19:01:26 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	set_minimap(t_cube *cube)
{
	cube->wall_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->wall_img)
		return (error_func("mlx_new_image"));
	cube->floor_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->floor_img)
		return (error_func("mlx_new_image"));
	cube->player = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->player)
		return (error_func("mlx_new_image"));
	cube->minimap_img = mlx_new_image(cube->mlx, 224, 224);
	if (!cube->minimap_img)
		return (error_func("mlx_new_image"));
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	mlx_image_to_window(cube->mlx, cube->minimap_img, 20, 20);
	mlx_image_to_window(cube->mlx, cube->player, 117, 117);
	mlx_set_instance_depth(&cube->minimap_img->instances[0], 1);
	mlx_set_instance_depth(&cube->player->instances[0], 2);
	return (0);
}
