/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:14 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 11:09:00 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	prepare_projection_data(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			calculate_projection(map, i, j);
			j++;
		}
		i++;
	}
}

void	allocate_grid_memory(t_map *map)
{
	int	i;

	map->grid3d = malloc(sizeof(t_point *) * map->rows);
	map->fgrid = malloc(sizeof(t_fpoint *) * map->rows);
	if (!map->grid3d || !map->fgrid)
	{
		release_memory(map);
		print_error_message(ENOMEM);
	}
	i = 0;
	while (i < map->rows)
	{
		map->grid3d[i] = malloc(sizeof(t_point) * map->cols);
		map->fgrid[i] = malloc(sizeof(t_fpoint) * map->cols);
		if (!map->grid3d[i] || !map->fgrid[i])
		{
			release_memory(map);
			print_error_message(ENOMEM);
		}
		i++;
	}
}

void	calculate_columns(t_map *map)
{
	int	column_count;
	int	i;

	column_count = 0;
	i = 0;
	while (map->grid2d[0][i])
	{
		if (is_valid_character(map->grid2d[0][i])
			&& (map->grid2d[0][i + 1] == ' '
			|| map->grid2d[0][i + 1] == '\n'
			|| map->grid2d[0][i + 1] == '\0'))
			column_count++;
		i++;
	}
	map->cols = column_count;
}

void	generate_matrix(t_map *map)
{
	int	i;

	calculate_columns(map);
	allocate_grid_memory(map);
	i = 0;
	while (i < map->rows)
	{
		populate_columns(map, i);
		i++;
	}
	adjust_scaling_factor(map);
	if (map->max > 10)
		map->vertical_scale = 0.1;
	else
		map->vertical_scale = 20;
}
