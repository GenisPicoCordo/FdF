/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:08:26 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 15:37:12 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	calculate_projection(t_map *map, int i, int j)
{
	map->fgrid[i][j].x = (int)(map->grid3d[i][j].x
			* map->scaling_factor)
		* sinf(map->projection_angle_alpha)
		+ ((int)map->grid3d[i][j].z
			* sinf(map->projection_angle_alpha - PI / 2)
			* map->vertical_scale);
	map->fgrid[i][j].y = (int)(map->grid3d[i][j].y
			* map->scaling_factor)
		* cosf(map->projection_angle_alpha)
		+ ((int)-map->grid3d[i][j].z
			* cosf(map->projection_angle_alpha - PI / 2)
			* map->vertical_scale);
	map->fgrid[i][j].x = (map->fgrid[i][j].x
			/ map->projection_angle_beta)
		- (map->fgrid[i][j].y / map->projection_angle_beta);
	map->fgrid[i][j].y = (map->fgrid[i][j].x
			/ map->projection_angle_beta)
		+ (map->fgrid[i][j].y / map->projection_angle_beta);
	map->fgrid[i][j].x *= map->zoom_level;
	map->fgrid[i][j].y *= map->zoom_level;
	assign_color_to_point(map, i, j);
}

void	populate_columns(t_map *map, int row)
{
	t_point	*point;
	char	**line_parts;
	int		col;

	line_parts = split_line(map->grid2d[row], ' ');
	col = 0;
	while (col < map->cols)
	{
		map->max = get_maximum(map->max,
				convert_to_int(line_parts[col]));
		map->min = get_minimum(map->min,
				convert_to_int(line_parts[col]));
		point = &map->grid3d[row][col];
		point->x = col;
		point->y = row;
		point->z = convert_to_int(line_parts[col]);
		point->colour = 0x00BCA1FF;
		if (contains_comma(line_parts[col]))
		{
			map->default_color = 1;
			point->colour = extract_color_from_line(line_parts[col]);
		}
		col++;
	}
	free_allocated_array((void **)line_parts);
}
