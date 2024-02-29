/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:16:48 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/29 13:26:42 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# ifndef WIDTH
#  define WIDTH 1024
# endif
# ifndef HEIGHT
#  define HEIGHT 1024
# endif

typedef struct s_cube
{
	mlx_t			*mlx;
	mlx_image_t		*player;
	int				map;
	mlx_image_t		*floor_img;
	mlx_texture_t	*floor_tex;
	mlx_image_t		*wall_img;
	mlx_texture_t	*wall_tex;
}				t_cube;

char	**render_map(t_cube *c, char **argv);
void	renderloop(mlx_t *mlx, char **map, t_cube *c);
int		check_map(char **map);
int		error_func(char *failed_func);
int		error_argc(void);
int		error_map(char *str);

#endif
