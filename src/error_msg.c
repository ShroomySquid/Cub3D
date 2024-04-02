/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:12:02 by fbarrett          #+#    #+#             */
/*   Updated: 2024/04/02 10:03:00 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube.h"

int	error_func(char *failed_func)
{
	printf("Function %s failed\n", failed_func);
	return (1);
}

int	error_argc(void)
{
	printf("Invalid amount of arguments\n");
	return (1);
}

int	error_map(char *str, int x, int y)
{
	printf("Invalid map: %s at x: %d, y: %d\n", str, x, y);
	return (1);
}

int	error_map_file(char *str)
{
	printf("Invalid map: %s\n", str);
	return (1);
}
