/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:16:48 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/17 15:09:11 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# ifndef FOV
#  define FOV 60
# endif
# ifndef WIDTH
#  define WIDTH 1024
# endif
# ifndef HEIGHT
#  define HEIGHT 1024
# endif

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

typedef struct s_cube
{
	mlx_texture_t	*lock_tex;
	mlx_image_t		*lock_img;
	mlx_t			*mlx;
	mlx_image_t		*player;
	float			playerx;
	float			playery;
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
	int				last_y;
	int				last_x;
}				t_cube;

int		is_cardinal(char *str, t_cube *cube);
int		check_cardinals(char *paths, t_cube *c);
int		array_len(char **array);
void	step_collision(float rotation, t_cube *cube, bool running);
float	*ft_getscale(t_cube c, float screenx, int *i);
void	step(float *x, float *y, float rotation, t_cube *c);
char	*whitespace_array(void);
int		set_minimap(t_cube *cube);
void	ft_player(void *param);
void	ft_general(void *param);
int		check_fc(int *i, char **data, t_cube *cube);
void	is_map_still_invalid(int *valid_map, t_cube *cube);
void	ft_render(void *param);
int32_t	get_rgba(int r, int g, int b, int a);
char	**parsing_map(t_cube *c, char **argv);
void	render_minimap(void *param);
int		check_map(char **map, t_cube *cube);
int		error_func(char *failed_func);
int		error_argc(void);
int		error_map(char *str);
int		check_textures(t_cube *cube);
int		is_whitespace(char c);
int		is_whitespace_str(char *str);
int		is_digit_str(char *str);
bool	touch_wall(char **map, int size, int x, int y);
void	render_player(void *param);

#endif
