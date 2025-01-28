/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:54:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/28 16:48:45 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	parse_tabs(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (ft_strchr(map->grid2d[i], '\t'))
			return (1);
		i++;
	}
	return (0);
}

int	parse_digits(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->grid2d[i][j])
		{
			if (ft_isalpha(map->grid2d[i][j]) && map->grid2d[i][j - 1]
					&& ft_isspace(map->grid2d[i][j - 1])
					&& map->grid2d[i][j + 1]
					&& ft_isspace(map->grid2d[i][j + 1]))
				return (1);
			else if (!ft_isalnum(map->grid2d[i][j])
				&& !ft_isspace(map->grid2d[i][j])
				&& map->grid2d[i][j] != ',' && map->grid2d[i][j] != '-')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_form(t_map *map)
{
	int	count;
	int	i;

	count = ft_count_words(map->grid2d[0]);
	i = 0;
	while (i < map->rows)
	{
		if (ft_count_words(map->grid2d[i]) != count)
			return (1);
		i++;
	}
	return (0);
}

int	parse_empty_line(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		if (ft_count_words(map->grid2d[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	parse_map(t_map *map)
{
	if (parse_tabs(map))
		return (ft_putendl_fd("Error: tabs not allowed", 2), 1);
	if (parse_digits(map))
		return (ft_putendl_fd("Error: invalid characters", 2), 1);
	if (parse_form(map))
		return (ft_putendl_fd("Error: irregular form", 2), 1);
	if (parse_empty_line(map))
		return (ft_putendl_fd("Error: nothing to render", 2), 1);
	return (0);
}
