/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:33 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 13:03:56 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Resets the image by filling it with a dark background color.
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

// Sets a basic 2D projection mode by scaling and positioning the points.
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
