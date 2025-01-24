/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:30:16 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 11:16:55 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	is_valid_character(char c)
{
	if (ft_isdigit(c) || c == '-' || c == '+')
		return (1);
	return (0);
}

int	convert_to_int(const char *str)
{
	return (ft_atoi(str));
}

int	contains_comma(const char *str)
{
	if (ft_strchr(str, ',') != NULL)
		return (1);
	return (0);
}

int	extract_color_from_line(const char *str)
{
	const char	*comma;
	int			color;

	comma = ft_strchr(str, ',');
	if (comma != NULL)
	{
		color = ft_atoi_base(comma + 1, 16);
		return (color);
	}
	return (0xFFFFFF);
}

char	**split_line(const char *str, char delimiter)
{
	return (ft_split(str, delimiter));
}
