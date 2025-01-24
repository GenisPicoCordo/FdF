/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:06:11 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 11:06:52 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	update_delta_values(t_delta *delta, t_fpoint start, t_fpoint end)
{
	delta->dx = end.x - start.x;
	delta->dy = end.y - start.y;
	if (fabs(delta->dx) >= fabs(delta->dy))
		delta->step_count = fabs(delta->dx);
	else
		delta->step_count = fabs(delta->dy);
	delta->dx /= delta->step_count;
	delta->dy /= delta->step_count;
	delta->x = start.x;
	delta->y = start.y;
}

void	draw_line_segment(t_fdf *fdf, t_fpoint start, t_fpoint end)
{
	t_delta	delta;
	int		i;

	update_delta_values(&delta, start, end);
	i = 0;
	while (i <= delta.step_count)
	{
		if (delta.x + fdf->map->width_offset > 0
			&& delta.x + fdf->map->width_offset < WINDOW_WIDTH
			&& delta.y + fdf->map->height_offset > 0
			&& delta.y + fdf->map->height_offset < WINDOW_HEIGHT)
		{
			mlx_put_pixel(fdf->img,
				delta.x + fdf->map->width_offset,
				delta.y + fdf->map->height_offset, start.colour);
		}
		delta.x += delta.dx;
		delta.y += delta.dy;
		i++;
	}
}

void	connect_grid_points(t_fdf *fdf, int x, int y)
{
	if (x < fdf->map->rows - 1)
		draw_line_segment(fdf, fdf->map->fgrid[x][y],
			fdf->map->fgrid[x + 1][y]);
	if (y < fdf->map->cols - 1)
		draw_line_segment(fdf, fdf->map->fgrid[x][y],
			fdf->map->fgrid[x][y + 1]);
}
