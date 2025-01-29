/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:14 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 13:03:17 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Checks if a character is a valid numeric character, including '-' and '+'.
int	is_valid_character(char c)
{
	if (ft_isdigit(c) || c == '-' || c == '+')
		return (1);
	return (0);
}

// Calculates the number of columns in the map by counting valid 
// numeric entries in the first row.
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

// Allocates memory for the 3D and floating-point grid structures.
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

// Adjusts the scaling factor based on the map size and window dimensions.
void	adjust_scaling_factor(t_map *map)
{
	int	interval_x;
	int	interval_y;

	interval_x = WINDOW_WIDTH / (map->cols * cosf(35));
	interval_y = WINDOW_HEIGHT / (map->rows * sinf(35));
	if (interval_x > interval_y)
		map->scaling_factor = -interval_y / 2;
	else
		map->scaling_factor = -interval_x / 2;
}

// Generates the matrix by determining the column count, allocating memory,
// populating data, and setting scaling.
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
