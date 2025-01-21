/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:17:10 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 18:46:54 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	apply_isometric_projection(int *x, int *y, int z)
{
	double	previous_x;
	double	previous_y;
	double	angle_x;
	double	angle_y;

	previous_x = *x;
	previous_y = *y;
	angle_x = 0.523599;
	angle_y = 0.523599;
	*x = (previous_x - previous_y) * cos(angle_x);
	*y = ((previous_x + previous_y) * sin(angle_y)) - z;
}

t_step	calculate_steps(t_line *line)
{
	t_step	step;
	float	dx;
	float	dy;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	if (fabs(dx) > fabs(dy))
		step.step = fabs(dx);
	else
		step.step = fabs(dy);
	step.x_step = dx / step.step;
	step.y_step = dy / step.step;
	return (step);
}

void	draw_pixels(mlx_image_t *img, t_line *line, \
	t_step *step, uint32_t color)
{
	float	x;
	float	y;
	int		i;

	x = line->x0;
	y = line->y0;
	i = 0;
	while (i <= (int)step->step)
	{
		if (is_pixel_in_bounds((int)x, (int)y))
			mlx_put_pixel(img, (int)x, (int)y, color);
		x += step->x_step;
		y += step->y_step;
		i++;
	}
}

void	draw_line_basic(mlx_image_t *img, t_line *line, uint32_t color)
{
	t_step	step;

	step = calculate_steps(line);
	draw_pixels(img, line, &step, color);
}

void	apply_transformations(t_line *line, t_draw_info *info)
{
	int	scale;
	int	offset_x;
	int	offset_y;

	scale = 40;
	offset_x = 960;
	offset_y = 300;
	apply_isometric_projection(&line->x0, &line->y0, info->z0 * scale / 8);
	apply_isometric_projection(&line->x1, &line->y1, info->z1 * scale / 8);
	line->x0 += offset_x;
	line->y0 += offset_y;
	line->x1 += offset_x;
	line->y1 += offset_y;
}
