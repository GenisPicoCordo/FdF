/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:33 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/28 12:43:42 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	assign_color_to_point(t_map *map, int i, int j)
{
	float	percentage;

	if (map->grid3d[i][j].colour != 0x00BCA1FF)
	{
		map->fgrid[i][j].colour = map->grid3d[i][j].colour;
	}
	else
	{
		percentage = calculate_color_percentage(map->max, \
			map->min, map->grid3d[i][j].z);
		map->fgrid[i][j].colour = get_color_based_on_percentage(percentage);
	}
}

void	reset_image(t_fdf *fdf)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < fdf->img->width)
	{
		j = 0;
		while (j < fdf->img->height)
		{
			mlx_put_pixel(fdf->img, i, j, 0x22222200);
			j++;
		}
		i++;
	}
}

void	set_2d_projection_mode(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			map->fgrid[i][j].x = (int)(map->grid3d[i][j].x \
				* map->scaling_factor);
			map->fgrid[i][j].y = (int)(map->grid3d[i][j].y \
				* map->scaling_factor);
			map->fgrid[i][j].x *= map->zoom_level;
			map->fgrid[i][j].y *= map->zoom_level;
			assign_color_to_point(map, i, j);
			j++;
		}
		i++;
	}
}
