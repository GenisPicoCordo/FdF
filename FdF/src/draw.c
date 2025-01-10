/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/10 10:23:29 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Crear una línea horizontal
static t_line	create_horizontal_line(int x, int y, t_map *map)
{
	t_line	line;
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = x * 20;
	y1 = y * 20;
	x2 = (x + 1) * 20;
	y2 = y * 20;
	isometric_projection(&x1, &y1, map->z_values[y][x]);
	isometric_projection(&x2, &y2, map->z_values[y][x + 1]);
	line.x0 = x1;
	line.y0 = y1;
	line.x1 = x2;
	line.y1 = y2;
	line.color = 0xFFFFFF;
	return (line);
}

// Crear una línea vertical
static t_line	create_vertical_line(int x, int y, t_map *map)
{
	t_line	line;
	int		x1;
	int		y1;
	int		x2;
	int		y2;

	x1 = x * 20;
	y1 = y * 20;
	x2 = x * 20;
	y2 = (y + 1) * 20;
	isometric_projection(&x1, &y1, map->z_values[y][x]);
	isometric_projection(&x2, &y2, map->z_values[y + 1][x]);
	line.x0 = x1;
	line.y0 = y1;
	line.x1 = x2;
	line.y1 = y2;
	line.color = 0xFFFFFF;
	return (line);
}

// Crear una línea en función de si es horizontal o vertical
static t_line	create_line(int x, int y, t_map *map, int is_horizontal)
{
	if (is_horizontal)
		return (create_horizontal_line(x, y, map));
	else
		return (create_vertical_line(x, y, map));
}

// Dibujar las líneas de una fila del mapa
static void	process_row(mlx_image_t *img, t_map *map, int y, int is_horizontal)
{
	int		x;
	t_line	line;
	int		limit;

	x = 0;
	if (is_horizontal)
		limit = map->width - 1;
	else
		limit = map->width;
	while (x < limit)
	{
		if (is_horizontal && x + 1 < map->width)
			line = create_line(x, y, map, 1);
		else if (!is_horizontal && y + 1 < map->height)
			line = create_line(x, y, map, 0);
		draw_line(img, &line);
		x++;
	}
}

// Dibujar todas las líneas del mapa
void	draw_map_lines(mlx_image_t *img, t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height - 1)
	{
		process_row(img, map, y, 1);
		process_row(img, map, y, 0);
		y++;
	}
	process_row(img, map, y, 1);
}
