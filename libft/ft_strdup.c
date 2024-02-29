/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:35:38 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/29 11:14:07 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		str_length;
	int		a;
	char	*new_str;

	if (!src)
		return (NULL);
	str_length = ft_strlen(src);
	a = 0;
	new_str = ft_calloc(str_length + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (a < str_length)
	{
		new_str[a] = src[a];
		a++;
	}
	new_str[a] = '\0';
	return (new_str);
}
