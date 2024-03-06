/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:16:48 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/06 11:17:08 by fbarrett         ###   ########.fr       */
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

typedef struct	s_map
{
	int 	fd;
	int		nbr_line;
	char	*NO;
	char 	*SO;
	char	*WE;
	char	*EA;
	int32_t	floor;
	int32_t	roof;
	char	**map;
}				t_map;

typedef struct s_cube
{
	mlx_t			*mlx;
	mlx_image_t		*player;
	mlx_image_t		*floor_img;
	mlx_texture_t	*floor_tex;
	mlx_image_t		*render;
	int				rotation;
	mlx_image_t		*wall_img;
	mlx_texture_t	*wall_tex;
	t_map			*map;
	int				map_nbr_line;
}				t_cube;

void	ft_render(void *param);
int32_t	get_rgba(int r, int g, int b, int a);
char	**render_map(t_cube *c, char **argv);
void	renderloop(mlx_t *mlx, char **map, t_cube *c);
int		check_map(t_cube *cube);
int		error_func(char *failed_func);
int		error_argc(void);
int		error_map(char *str);
int		check_textures(t_cube *cube);
int		is_whitespace(char c);
int		is_whitespace_str(char *str);
int		is_digit_str(char *str);

#endif
