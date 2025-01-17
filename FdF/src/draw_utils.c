/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:17:10 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 13:51:45 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

void	draw_line(t_draw_params *params, t_line *line)
{
	float	x;
	float	y;
	float	inc_x;
	float	inc_y;
	float	step;

	x = line->x0;
	y = line->y0;
	calculate_increments(line, &inc_x, &inc_y, &step);
	while ((int)step >= 0)
	{
		if (is_pixel_in_bounds((int)x, (int)y))
			mlx_put_pixel(params->img, (int)x, (int)y, line->color);
		x += inc_x;
		y += inc_y;
		step -= 1;
	}
}

void	set_z_values(t_draw_params *params, int direction, int *z0, int *z1)
{
	*z0 = (params->x + params->y) % 2;
	if (direction == 0)
		*z1 = ((params->x + 1) + params->y) % 2;
	else
		*z1 = (params->x + (params->y + 1)) % 2;
}
