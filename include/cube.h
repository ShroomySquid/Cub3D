/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:16:48 by fbarrett          #+#    #+#             */
/*   Updated: 2024/04/02 10:02:08 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# ifndef SIZE
#  define SIZE 32
# endif
# ifndef FOV
#  define FOV 60
# endif
# ifndef WIDTH
#  define WIDTH 1024
# endif
# ifndef HEIGHT
#  define HEIGHT 1024
# endif

typedef struct s_side
{
	float	last_x;
	float	last_y;
	int		coord[2];
	int		last_coord[2];	
}				t_side;

typedef struct s_mov
{
	bool	down;
	bool	left;
	bool	right;
	bool	up;
	float	speed;
}				t_mov;

typedef struct s_scale
{
	float	angle;
	float	hypo;
	float	oppo;
	float	size;
	float	teta;
	float	x;
	float	y;
	int		x_div;
	int		y_div;
}				t_scale;

typedef struct s_minimap
{
	char		coord;
	int			min_y;
	int			min_x;
	int			x;
	int			y;
}				t_minimap;

typedef struct s_map
{
	int			fd;
	int			nbr_line;
	mlx_image_t	***walls;
	int32_t		floor;
	int32_t		roof;
	char		**map;
	int			car;
}				t_map;

typedef struct s_wall
{
	bool		draw;
	mlx_image_t	*img;
	float		scale;
	int			side;
	int			x;
}				t_wall;

typedef struct s_cube
{
	bool			draw_map;
	bool			draw_player;
	bool			draw_screen;
	mlx_texture_t	*lockh_tex;
	mlx_image_t		*lockh_img;
	mlx_texture_t	*lockv_tex;
	mlx_image_t		*lockv_img;
	mlx_t			*mlx;
	mlx_image_t		*player;
	float			playerx;
	float			playery;
	float			radian;
	int				half_fov;
	int				height_div;
	int				width_div;
	mlx_image_t		*floor_img;
	mlx_texture_t	*floor_tex;
	mlx_image_t		*pointer;
	mlx_texture_t	*pointer_tex;
	mlx_image_t		*render;
	float			rotation;
	mlx_image_t		*wall_img;
	mlx_texture_t	*wall_tex;
	t_map			*map;
	mlx_image_t		*minimap_img;
	int				map_nbr_line;
	int				last_line;
	float			step_x;
	float			step_y;
	int				is_mini_active;
	int				is_light_active;
	bool			first;
	int32_t			height_img;
	int32_t			width_img;
}				t_cube;

void	ft_send(t_scale *scale, t_cube *cube);
void	ft_mouse(t_cube *c);
void	ft_movement(bool running, t_cube *cube);
int		force_exit(t_cube *cube);
int		check_extension(char **argv);
int		is_cardinal(char *str, t_cube *cube);
int		check_cardinals(char *paths, t_cube *c);
int		array_len(char **array);
void	step_collision(float rotation, t_cube *cube, float speed);
t_wall	ft_getscale(t_cube c, int screenx, int *i);
void	step(float *x, float *y, t_cube *c, float distance);
void	reverse_step(float *x, float *y, t_cube *c, float distance);
char	*whitespace_array(void);
int		set_minimap(t_cube *cube);
void	ft_player(void *param);
void	ft_general(mlx_key_data_t data, void *param);
int		check_fc(int *i, char **data, t_cube *cube);
void	is_map_still_invalid(int *valid_map, t_cube *cube);
void	ft_render(void *param);
int32_t	get_rgba(int r, int g, int b, int a);
char	**parsing_map(t_cube *c, char **argv);
void	render_minimap(void *param);
int		check_map(char **map, t_cube *cube, int x, int y);
int		error_func(char *failed_func);
int		error_argc(void);
int		error_map(char *str, int x, int y);
int		error_map_file(char *str);
int		check_textures(t_cube *cube);
int		is_whitespace(char c);
int		is_whitespace_str(char *str);
int		is_digit_str(char *str);
bool	touch_wall(char **map, int size, int x, int y);
void	render_player(void *param);
int		is_mini_down(t_cube *c);
void	calculate_step(float rotation, t_cube *c);
int32_t	get_pixel(mlx_image_t *img, int x, int y);
void	ft_image(t_cube *cube);
void	ft_render_loop(t_cube *cube, int x, int *i);
int		ft_getside(float x, float y, t_cube *c);
int32_t	get_color_mini(t_minimap *mini, t_cube *c);
void	draw_los(float los, t_cube *cube);

#endif
