/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:31:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/20 12:47:09 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_line_coordinates(t_draw_params *params, t_line *line, int direction)
{
	line->x0 = params->x * params->spacing;
	line->y0 = params->y * params->spacing;
	if (direction == 0)
	{
		line->x1 = (params->x + 1) * params->spacing;
		line->y1 = params->y * params->spacing;
	}
	else
	{
		line->x1 = params->x * params->spacing;
		line->y1 = (params->y + 1) * params->spacing;
	}
}

void	calculate_increments(t_line *line, float *inc_x, \
	float *inc_y, float *step)
{
	float	diff_x;
	float	diff_y;

	diff_x = line->x1 - line->x0;
	diff_y = line->y1 - line->y0;
	if (fabs(diff_x) > fabs(diff_y))
		*step = fabs(diff_x);
	else
		*step = fabs(diff_y);
	*inc_x = diff_x / *step;
	*inc_y = diff_y / *step;
}

void	set_z_values(t_draw_params *params, int direction, int *z0, int *z1)
{
	*z0 = (params->x + params->y) % 2;
	if (direction == 0)
		*z1 = ((params->x + 1) + params->y) % 2;
	else
		*z1 = (params->x + (params->y + 1)) % 2;
}

int	is_pixel_in_bounds(int x, int y)
{
	return (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT);
}
