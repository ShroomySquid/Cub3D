/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 11:16:55 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	get_color(int len, int i, char *line)
{
	char	*temp_color;
	int		color;

	temp_color = ft_substr(line, i, len);
	if (!temp_color)
		return (error_func("ft_substr"), -1);
	if (!is_digit_str(temp_color))
		return (free(temp_color), error_map("Invalid color for rgb"), -1);
	color = ft_atoi(temp_color);
	free (temp_color);
	if (color > 255 || color < 0)
		return (error_map("Invalid color for rgb"), -1);
	return (color);
}

int	check_color_len(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i + len] && line[i + len] != ',' && line[i + len] != '\n')
		len++;
	return (len);
}

int	check_fc(int *data, char *line, int *valid_map, t_cube *cube)
{
	int		*rgb;
	int		i;
	int		len;
	int		rgb_len;

	if (*data != -1)
		return (1);
	rgb = malloc(sizeof(int) * 4);
	if (!rgb)
		return (error_func("malloc"));
	i = 2;
	rgb_len = 0;
	while (rgb_len < 3)
	{
		len = check_color_len(line, i);
		if (len > 3 || len < 1)
			return (free(rgb), error_map("Invalid color for rgb"));
		rgb[rgb_len] = get_color(len, i, line);
		if (rgb[rgb_len] == -1)
			return (free(rgb), 1);
		rgb_len++;
		i += len + 1;
	}
	*data = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	return (free(rgb), is_map_still_invalid(valid_map, cube), 0);
}
