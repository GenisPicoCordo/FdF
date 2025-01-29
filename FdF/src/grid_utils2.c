/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:24 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 13:01:25 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Splits a string into an array of substrings using a given delimiter.
char	**split_line(const char *str, char delimiter)
{
	return (ft_split(str, delimiter));
}

// Returns the maximum of two integer values.
int	get_maximum(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

// Returns the minimum of two integer values.
int	get_minimum(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

// Converts a string to an integer.
int	convert_to_int(const char *str)
{
	return (ft_atoi(str));
}

// Checks if a string contains a comma.
int	contains_comma(const char *str)
{
	if (ft_strchr(str, ',') != NULL)
		return (1);
	return (0);
}
