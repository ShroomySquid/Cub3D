/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 14:19:28 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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

void	innit_cube(t_cube *cube)
{
	cube->floor_tex = NULL;
	cube->lockh_tex = NULL;
	cube->lockv_tex = NULL;
	cube->wall_tex = NULL;
	cube->pointer_tex = NULL;
	cube->precalc = M_PI / 180;
	cube->precalc2 = FOV / 2.0;
	cube->first = true;
	cube->width_img = 0;
	cube->height_img = 0;
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
		return (error_argc());
	if (check_extension(argv))
		return (error_map("Invalid extension"));
	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (error_func("malloc"));
	innit_cube(cube);
	cube->map = malloc(sizeof(t_map));
	if (!cube->map)
		return (free(cube), error_func("malloc"));
	cube->map->walls = malloc(6 * sizeof(mlx_image_t **));
	cube->map->walls[0] = NULL;
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
