/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:16:48 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/08 18:35:37 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
#include <math.h>
# include <stdio.h>
# ifndef WIDTH
#  define WIDTH 1024
# endif
# ifndef HEIGHT
#  define HEIGHT 1024
# endif
# ifndef X_MIN
#  define X_MIN -768
# endif
# ifndef X_MAX
#  define X_MAX 1791
# endif
# ifndef Y_MIN
#  define Y_MIN -138
# endif
# ifndef Y_MAX
#  define Y_MAX 1301
# endif

typedef struct s_map
{
	int 		fd;
	int			nbr_line;
	mlx_image_t ***walls;
	int32_t		floor;
	int32_t		roof;
	char		**map;
	int			car;
}				t_map;

typedef struct s_cube
{
	mlx_t			*mlx;
	mlx_image_t		*player;
	float			playerx;
	float			playery;
	mlx_image_t		*floor_img;
	mlx_texture_t	*floor_tex;
	mlx_image_t		*render;
	int				rotation;
	mlx_image_t		*wall_img;
	mlx_texture_t	*wall_tex;
	t_map			*map;
	int				map_nbr_line;
}				t_cube;

char	*whitespace_array(void);
int		set_minimap(t_cube *cube);
void	ft_player(void *param);
void	ft_general(void *param);
int		check_fc(int *i, char **data, t_cube *cube);
void	is_map_still_invalid(int *valid_map, t_cube *cube);
void	ft_render(void *param);
int32_t	get_rgba(int r, int g, int b, int a);
char	**parsing_map(t_cube *c, char **argv);
void	render_minimap(mlx_t *mlx, char **map, t_cube *c);
int		check_map(char **map, t_cube *cube);
int		error_func(char *failed_func);
int		error_argc(void);
int		error_map(char *str);
int		check_textures(t_cube *cube);
int		is_whitespace(char c);
int		is_whitespace_str(char *str);
int		is_digit_str(char *str);
int		touch_wall(t_cube *cube, int x, int y);

#endif
