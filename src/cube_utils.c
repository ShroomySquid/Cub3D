/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:34:36 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/15 10:18:56 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

char	*whitespace_array(void)
{
	char	*whitespaces;

	whitespaces = malloc(7 * sizeof(char));
	if (!whitespaces)
		return (NULL);
	whitespaces[0] = 32;
	whitespaces[1] = 9;
	whitespaces[2] = 10;
	whitespaces[3] = 11;
	whitespaces[4] = 12;
	whitespaces[5] = 13;
	whitespaces[6] = 0;
	return (whitespaces);
}

int	is_whitespace(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

int	is_whitespace_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && is_whitespace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
