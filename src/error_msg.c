/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/02/28 14:12:01 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int error_func(char *failed_func)
{
	printf("Function %s failed\n", failed_func);
	return (1);
}

int error_argc(void)
{
	printf("Invalid amount of arguments\n");
	return (1);
}

int error_map(char *str)
{
	printf("Invalid map: %s\n", str);
	return (1);
}
