/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:28:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/29 10:41:33 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* retourne la dernière node de la liste chainée */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp_list;

	if (!lst)
		return (0);
	if (!lst->next)
		return (lst);
	temp_list = lst;
	while (temp_list->next)
		temp_list = temp_list->next;
	return (temp_list);
}
