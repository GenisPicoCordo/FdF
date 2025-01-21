/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 19:04:50 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_line_points(t_line *line, t_draw_info *info, int is_horizontal)
{
	int	scale;

	scale = 40;
	if (is_horizontal)
	{
		line->x0 = info->x * scale + info->offset_x;
		line->y0 = info->y * scale + info->offset_y;
		line->x1 = (info->x + 1) * scale + info->offset_x;
		line->y1 = info->y * scale + info->offset_y;
	}
	else
	{
		line->x0 = info->x * scale + info->offset_x;
		line->y0 = info->y * scale + info->offset_y;
		line->x1 = info->x * scale + info->offset_x;
		line->y1 = (info->y + 1) * scale + info->offset_y;
	}
}

void	draw_grid_line(t_draw_info *info, int is_horizontal, uint32_t color)
{
	t_line	line;

	set_line_points(&line, info, is_horizontal);
	apply_transformations(&line, info);
	draw_line_basic(info->img, &line, color);
}

void	set_info_values(t_draw_info *info, mlx_image_t *img, int x, int y)
{
	info->img = img;
	info->x = x;
	info->y = y;
}

void	draw_grid_segments(t_draw_info *info, t_map *map, int x, int y)
{
	uint32_t	color;

	if (x < map->width - 1)
	{
		info->z0 = map->z_values[y][x];
		info->z1 = map->z_values[y][x + 1];
		color = get_color(info->z0, map->min_z, map->max_z);
		draw_grid_line(info, 1, color);
	}
	if (y < map->height - 1)
	{
		info->z0 = map->z_values[y][x];
		info->z1 = map->z_values[y + 1][x];
		color = get_color(info->z0, map->min_z, map->max_z);
		draw_grid_line(info, 0, color);
	}
}

void	draw_isometric_grid(mlx_image_t *img, t_map *map, \
	int window_width, int window_height)
{
	t_draw_info	info;
	int			x;
	int			y;

	info.scale = 40;
	info.offset_x = (window_width - map->width * info.scale) / 2;
	info.offset_y = (window_height - map->height * info.scale) / 2;
	info.img = img;
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
