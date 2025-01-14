/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/14 17:53:45 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Calcula el espaciado y los offsets para centrar el mapa
void	calculate_spacing_and_offsets(t_map *map, t_params *params)
{
	int	spacing_x;
	int	spacing_y;

	spacing_x = 1920 / (map->width + map->height);
	spacing_y = 1080 / (map->width + map->height);
	if (spacing_x < spacing_y)
		params->spacing = spacing_x;
	else
		params->spacing = spacing_y;
	params->offset_x = 1100 - ((map->width - 1) \
		* params->spacing * cos(0.523599)) / 2;
	params->offset_y = 150 - ((map->height - 1) \
		* params->spacing * sin(0.523599)) / 2;
}

// Dibuja una línea en la cuadrícula (horizontal o vertical)
void	draw_grid_line(mlx_image_t *img, t_line *line, \
	t_map *map, t_params *params)
{
	isometric_projection(&line->x0, &line->y0, \
		map->z_values[line->y0][line->x0]);
	isometric_projection(&line->x1, &line->y1, \
		map->z_values[line->y1][line->x1]);
	line->x0 = line->x0 * params->spacing + params->offset_x;
	line->y0 = line->y0 * params->spacing + params->offset_y;
	line->x1 = line->x1 * params->spacing + params->offset_x;
	line->y1 = line->y1 * params->spacing + params->offset_y;
	draw_line_basic(img, line, line->color);
}

// Dibuja una línea horizontal en la cuadrícula
void	draw_grid_horizontal(mlx_image_t *img, \
	t_draw_params *draw_params, int x, int y)
{
	t_line	line;

	line = (t_line){x, y, x + 1, y, 0xFF00FFFF};
	draw_grid_line(img, &line, draw_params->map, draw_params->params);
}

// Dibuja una línea vertical en la cuadrícula
void	draw_grid_vertical(mlx_image_t *img, \
	t_draw_params *draw_params, int x, int y)
{
	t_line	line;

	line = (t_line){x, y, x, y + 1, 0xFFFF00FF};
	draw_grid_line(img, &line, draw_params->map, draw_params->params);
}

// Función principal para dibujar la cuadrícula
void	draw_grid(mlx_image_t *img, t_map *map)
{
	t_params		params;
	t_draw_params	draw_params;
	int				x;
	int				y;

	calculate_spacing_and_offsets(map, &params);
	draw_params = (t_draw_params){map, &params};
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				draw_grid_horizontal(img, &draw_params, x, y);
			if (y < map->height - 1)
				draw_grid_vertical(img, &draw_params, x, y);
			x++;
		}
		y++;
	}
}
