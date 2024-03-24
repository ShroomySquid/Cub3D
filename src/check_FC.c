/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:50:21 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/24 10:18:18 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	get_color(int len, char *color)
{
	char	*temp_color;
	int		color_int;

	temp_color = ft_substr(color, 0, len);
	if (!temp_color)
		return (error_func("ft_substr"), -1);
	if (!is_digit_str(temp_color))
		return (free(temp_color), error_map("Invalid color for rgb"), -1);
	color_int = ft_atoi(temp_color);
	free(temp_color);
	if (color_int > 255 || color_int < 0)
		return (error_map("Invalid color for rgb"), -1);
	return (color_int);
}

int	check_color_len(char *line)
{
	int	len;

	len = 0;
	if (line[0] == ',')
		len++;
	while (line[len] && ft_isdigit(line[len]) && len < 4)
		len++;
	if (!ft_isdigit(line[len]) && line[len] != ',')
		return (0);
	return (len);
}

int	extra_color(char *color, int *a)
{
	if (color[*a] == ',')
		*a += 1;
	while (color[*a] && color[*a] != ',')
		*a += 1;
	if (color[*a])
		*a += 1;
	if (color[*a])
		return (*a);
	else
	{
		*a = 0;
		return (0);
	}
}

int	parse_rgba(char **data, int *i, int *rgb)
{
	int	a;
	int	len;
	int	rgb_len;

	a = 0;
	rgb_len = 0;
	while (data[*i] && rgb_len < 3)
	{
		if (data[*i][a] && data[*i][a] == ',')
			a++;
		len = check_color_len(&data[*i][a]);
		if (len > 3 || len < 1)
			return (error_map("Invalid color for rgb"));
		rgb[rgb_len] = get_color(len, &data[*i][a]);
		if (rgb[rgb_len] == -1)
			return (1);
		rgb_len++;
		if (!extra_color(data[*i], &a))
			*i += 1;
		if (data[*i] && data[*i][0] && data[*i][0] == ',' && !data[*i][1])
			*i += 1;
	}
	if (rgb_len < 3)
		return (error_map("Invalid amount of color for map"));
	return (0);
}

int	check_fc(int *i, char **data, t_cube *cube)
{
	int		*rgb;
	int		fc;

	fc = 0;
	if (ft_strnstr(data[*i - 1], "C", 2))
		fc = 1;
	if ((fc && cube->map->roof != -1) || (!fc && cube->map->floor != -1))
		return (error_map("Multiple color provided for same element"));
	if (!data[*i])
		return (error_map("No color provided for element"));
	rgb = malloc(sizeof(int) * 4);
	if (!rgb)
		return (error_func("malloc"));
	if (!ft_isdigit(data[*i][0]))
		return (free(rgb), error_map("Invalid color provided for element"));
	if (parse_rgba(data, i, rgb))
		return (free(rgb), 1);
	if (fc)
		cube->map->roof = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	else
		cube->map->floor = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	return (free(rgb), 0);
}
