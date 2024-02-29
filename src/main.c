/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/28 11:04:00 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int error_msg(char *failed_func)
{
	printf("Function %s failed\n", failed_func);
	return (1);
}

int32_t get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_player(void *param)
{
	t_cube	*cube;

	cube = param;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
		cube->player->instances[0].y -= 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_UP))
		cube->player->instances[0].y -= 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
		cube->player->instances[0].y += 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_DOWN))
		cube->player->instances[0].y += 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
		cube->player->instances[0].x -= 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
		cube->player->instances[0].x -= 2;
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
		cube->player->instances[0].x += 2;
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
		cube->player->instances[0].x += 2;
}

void	ft_general(void *param)
{
	t_cube	*cube;

	cube = param;	
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cube->mlx);		
}

int	touch_tile(char **map, char c, int x, int y)
{
	return (map[y / 32][x / 32] == c);
}

int	ft_getscale(t_cube *cube, float x, float screenx, int y)
{
	float	xinit;
	int		yinit;

	screenx -= 1024.0 / 2.0;
	x -= 16;
	screenx /= 512.0;
	printf("%f\n", screenx);
	yinit = y;
	xinit = x;
	while (y--)
	{
		x += screenx;
		if (touch_tile(cube->map, '1', x, y))
			return (yinit - y);
	}
	return (HEIGHT - (abs(yinit - y) + abs((int)xinit - (int)x)));
}

void	ft_render(void *param)
{
	t_cube		*cube;
	static bool	done = false;
	int			x;
	int			y;
	int			scale;

	cube = param;
	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		scale = HEIGHT - ft_getscale(cube, cube->player->instances[0].x + (float)x / 32, (float)x, cube->player->instances[0].y) * 4;
		while (++y < HEIGHT)
		{
			if (y < HEIGHT / 2 - scale / 2 || y >= HEIGHT / 2 + scale / 2)
			{
				if (y < HEIGHT / 2)
					mlx_put_pixel(cube->render, x, y, get_rgba(0xFF, 0x00, 0x00, 0xFF));
				else
					mlx_put_pixel(cube->render, x, y, get_rgba(0x00, 0x00, 0xFF, 0xFF));
			}
			else
				mlx_put_pixel(cube->render, x, y, get_rgba(0x00, 0xFF, 0x00, 0xFF));
		}
	}
	if (!done)
	{
		mlx_image_to_window(cube->mlx, cube->render, 0, 0);
		mlx_set_instance_depth(&cube->render->instances[0], 0);
		done = true;
	}
}

int main(int argc, char **argv)
{
	t_cube	*cube;

	(void)argc;
	(void)argv;
	cube = ft_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (error_msg("ft_calloc"));
	cube->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!cube->mlx)
		return (error_msg("mlx_init"));
	cube->wall_img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->wall_img)
		return (error_msg("mlx_new_image"));
	cube->floor_img = mlx_new_image(cube->mlx, 32, 32);
	if (!cube->floor_img)
		return (error_msg("mlx_new_image"));
	cube->player = mlx_new_image(cube->mlx, 4, 4);
	if (!cube->player)
		return (error_msg("mlx_new_image"));
	cube->render = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	if (!cube->render)
		return (error_msg("mlx_new_image"));
	cube->mapfd = open(argv[1], O_RDONLY);
	ft_memset(cube->player->pixels, 255, cube->player->width * cube->player->height * sizeof(int32_t));
	cube->wall_tex = mlx_load_png("./png/square-32(1).png");
	cube->floor_tex = mlx_load_png("./png/square-32.png");
	cube->wall_img = mlx_texture_to_image(cube->mlx, cube->wall_tex);
	cube->floor_img = mlx_texture_to_image(cube->mlx, cube->floor_tex);
	cube->map = render_map(cube);
	//mlx_image_to_window(cube->mlx, cube->map, 0, 0);
	//mlx_image_to_window(cube->mlx, cube->random_img, 32, 32);
	mlx_image_to_window(cube->mlx, cube->player, 64, 64);
	mlx_loop_hook(cube->mlx, ft_general, cube);
	mlx_loop_hook(cube->mlx, ft_player, cube);
	mlx_loop_hook(cube->mlx, ft_render, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	return (0);
}
