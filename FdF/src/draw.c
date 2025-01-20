/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/20 12:59:44 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_line_points(t_line *line, t_draw_info *info, int is_horizontal)
{
	int	scale;

	scale = 40;
	if (is_horizontal)
	{
		line->x0 = info->x * scale;
		line->y0 = info->y * scale;
		line->x1 = (info->x + 1) * scale;
		line->y1 = info->y * scale;
	}
	else
	{
		line->x0 = info->x * scale;
		line->y0 = info->y * scale;
		line->x1 = info->x * scale;
		line->y1 = (info->y + 1) * scale;
	}
}

void	draw_grid_line(t_draw_info *info, int is_horizontal)
{
	t_line	line;

	set_line_points(&line, info, is_horizontal);
	apply_transformations(&line, info);
	draw_line_basic(info->img, &line, 0xFFFFFFFF);
}

void	set_info_values(t_draw_info *info, mlx_image_t *img, int x, int y)
{
	info->img = img;
	info->x = x;
	info->y = y;
}

void	draw_grid_segments(t_draw_info *info, t_map *map, int x, int y)
{
	if (x < map->width - 1)
	{
		info->z0 = map->z_values[y][x];
		info->z1 = map->z_values[y][x + 1];
		draw_grid_line(info, 1);
	}
	if (y < map->height - 1)
	{
		info->z0 = map->z_values[y][x];
		info->z1 = map->z_values[y + 1][x];
		draw_grid_line(info, 0);
	}
}

void	draw_isometric_grid(mlx_image_t *img, t_map *map)
{
	t_draw_info	info;
	int			x;
	int			y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			set_info_values(&info, img, x, y);
			draw_grid_segments(&info, map, x, y);
		}
	}
}
