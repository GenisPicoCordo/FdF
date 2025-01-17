/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:31:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 12:32:51 by gpico-co         ###   ########.fr       */
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

void	apply_offset(t_line *line, t_draw_params *params)
{
	line->x0 += params->offset_x;
	line->y0 += params->offset_y;
	line->x1 += params->offset_x;
	line->y1 += params->offset_y;
}

void	setup_line(t_draw_params *params, t_line *line, int direction)
{
	int	z0;
	int	z1;

	if (!params->is_boundary)
		set_z_values(params, direction, &z0, &z1);
	else
		z0 = 0;
	z1 = 0;
	set_line_coordinates(params, line, direction);
	apply_isometric_projection(&line->x0, &line->y0, z0);
	apply_isometric_projection(&line->x1, &line->y1, z1);
	apply_offset(line, params);
}
