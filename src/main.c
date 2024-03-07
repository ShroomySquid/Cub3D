/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 13:17:00 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

void	set_player(t_cube *cube)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (x < cube->player->width)
	{
		while (y < cube->player->height)
		{
			mlx_put_pixel(cube->player, x, y, get_rgba(255, 255, 255, 255));
			y++;
		}
		y = 0;
		x++;
	}
}

void	force_exit(t_cube *cube)
{
	if (cube && cube->map && cube->map->map)
		free_all(cube->map->map);
	if (cube && cube->map)
		free(cube->map);
	if (cube)
		free(cube);
	mlx_terminate(cube->mlx);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
		return (error_argc());
	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (error_func("malloc"));
	cube->rotation = 1;
	cube->map = malloc(sizeof(t_map));
	if (!cube->map)
		return (error_func("malloc"));
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D\n", true);
	if (!cube->mlx)
		return (force_exit(cube), error_func("mlx_init"));
	cube->map->map = parsing_map(cube, argv);
	if (!cube->map->map)
		return (force_exit(cube), 1);
	if (check_map(cube->map->map, cube))
		return (force_exit(cube), 1);
	cube->wall_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->wall_img)
		return (force_exit(cube), error_func("mlx_new_image"));
	cube->render = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->render)
		return (force_exit(cube), error_func("mlx_new_image"));
	cube->floor_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->floor_img)
		return (force_exit(cube), error_func("mlx_new_image"));
	cube->player = mlx_new_image(cube->mlx, 4, 4);
	if (!cube->player)
		return (force_exit(cube), error_func("mlx_new_image"));
	set_player(cube);
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	render_minimap(cube->mlx, cube->map->map, cube);
	cube->playerx = cube->player->instances[0].x;
	cube->playery = cube->player->instances[0].y;
	mlx_loop_hook(cube->mlx, ft_general, cube);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop_hook(cube->mlx, ft_render, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	return (0);
}
