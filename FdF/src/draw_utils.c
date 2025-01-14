/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:17:10 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/14 16:27:12 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Inicializa las variables para el algoritmo de Bresenham
void	init_bresenham(t_bresenham *b, t_line *line)
{
	b->dx = abs(line->x1 - line->x0);
	b->dy = abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		b->sx = 1;
	else
		b->sx = -1;
	if (line->y0 < line->y1)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx - b->dy;
}

// Verifica si un píxel está dentro de los límites de la ventana
int	is_pixel_in_bounds(int x, int y)
{
	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
		return (1);
	return (0);
}

// Dibuja una línea usando el algoritmo de Bresenham
void	draw_line_basic(mlx_image_t *img, t_line *line, uint32_t color)
{
	t_bresenham	b;

	init_bresenham(&b, line);
	while (1)
	{
		if (is_pixel_in_bounds(line->x0, line->y0))
			mlx_put_pixel(img, line->x0, line->y0, color);
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		if (2 * b.err > -b.dy)
		{
			b.err -= b.dy;
			line->x0 += b.sx;
		}
		if (2 * b.err < b.dx)
		{
			b.err += b.dx;
			line->y0 += b.sy;
		}
	}
}
