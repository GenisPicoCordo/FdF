/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:17:10 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/10 09:46:07 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Dibujar un píxel y actualizar las coordenadas según las reglas de Bresenham
static int	update_coords(mlx_image_t *img, t_line *line, t_vars *vars)
{
	if (line->x0 < 0 || line->x0 >= 800 || line->y0 < 0 || line->y0 >= 600)
		return (0);
	mlx_put_pixel(img, line->x0, line->y0, line->color);
	if (line->x0 == line->x1 && line->y0 == line->y1)
		return (0);
	if (2 * vars->err >= vars->dy)
	{
		vars->err += vars->dy;
		line->x0 += vars->sx;
	}
	if (2 * vars->err <= vars->dx)
	{
		vars->err += vars->dx;
		line->y0 += vars->sy;
	}
	return (1);
}

void	init_vars(t_vars *vars, t_line *line)
{
	if (!vars || !line)
	{
		printf("Error: Puntero NULL en init_vars\n");
		return ;
	}
	vars->dx = abs(line->x1 - line->x0);
	vars->dy = -abs(line->y1 - line->y0);
	if (line->x0 < line->x1)
		vars->sx = 1;
	else
		vars->sx = -1;
	if (line->y0 < line->y1)
		vars->sy = 1;
	else
		vars->sy = -1;
	vars->err = vars->dx + vars->dy;
}

// Función principal para dibujar la línea
void	draw_line(mlx_image_t *img, t_line *line)
{
	t_vars	vars;

	if (!img || !line)
	{
		printf("Error: Puntero NULL en draw_line\n");
		return ;
	}
	init_vars(&vars, line);
	while (update_coords(img, line, &vars))
		;
}
