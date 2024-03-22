/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/19 12:58:55 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	free_walls(mlx_image_t ***array)
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
	mlx_delete_texture(cube->floor_tex);
	mlx_delete_texture(cube->wall_tex);
	mlx_delete_texture(cube->lockh_tex);
	mlx_delete_texture(cube->lockv_tex);
	mlx_delete_texture(cube->pointer_tex);
	mlx_terminate(cube->mlx);
	if (cube && cube->map && cube->map->walls)
		free_walls(cube->map->walls);
	if (cube && cube->map && cube->map->map)
		free_all(cube->map->map);
	if (cube && cube->map)
		free(cube->map);
	if (cube)
		free(cube);
	return (1);
}

int	start_cube(t_cube *cube)
{
	mlx_set_cursor_mode(cube->mlx, 0x00034002);
	cube->is_light_active = 1;
	cube->step_x = 0.0;
	cube->step_y = 0.0;
	if (cube->mlx->width < 512 || cube->mlx->height < 512)
		cube->is_mini_active = 0;
	else
		cube->is_mini_active = 1;
	if (set_minimap(cube))
		return (1);
	mlx_key_hook(cube->mlx, ft_general, cube);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop_hook(cube->mlx, ft_render, cube);
	mlx_loop_hook(cube->mlx, render_minimap, cube);
	mlx_loop_hook(cube->mlx, render_player, cube);
	mlx_loop(cube->mlx);
	return (0);
}

int	parsing(t_cube *cube, char **argv)
{
	cube->map->map = parsing_map(cube, argv);
	if (!cube->map->map)
		return (force_exit(cube));
	if (check_map(cube->map->map, cube, 0, 0))
		return (force_exit(cube));
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
		return (error_argc());
	cube = malloc(sizeof(t_cube));
	cube->precalc = M_PI / 180;
	cube->precalc2 = FOV / 2.0;
	if (!cube)
		return (error_func("malloc"));
	cube->map = malloc(sizeof(t_map));
	if (!cube->map)
		return (free(cube), error_func("malloc"));
	cube->map->walls = malloc(6 * sizeof(mlx_image_t **));
	if (!cube->map->walls)
		return (error_func("malloc"), force_exit(cube));
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D\n", true);
	if (!cube->mlx)
		return (force_exit(cube), error_func("mlx_init"));
	if (parsing(cube, argv))
		return (1);
	if (start_cube(cube))
		return (force_exit(cube));
	return (force_exit(cube), 0);
}
