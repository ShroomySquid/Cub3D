/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 08:34:36 by fbarrett          #+#    #+#             */
/*   Updated: 2024/03/07 11:19:59 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

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
