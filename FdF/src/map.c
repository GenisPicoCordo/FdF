/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:16:23 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 19:03:18 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_map_dimensions(const char *filename, int *width, int *height)
{
	int	fd;
	int	result;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	result = count_lines_and_width(fd, width, height);
	close(fd);
	return (result);
}

t_map	*init_map(int width, int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->width = width;
	map->height = height;
	map->z_values = allocate_z_values(width, height);
	if (!map->z_values)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	read_lines_to_map(int fd, t_map *map, int width, int height)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line && y < height)
	{
		if (!process_line(line, map, y, width))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
	if (line)
		free(line);
	scale_z_values(map);
	return (1);
}

// Función para inicializar el mapa y establecer valores iniciales
t_map	*initialize_map(const char *filename, int *width, int *height)
{
	t_map	*map;

	if (!get_map_dimensions(filename, width, height))
		return (NULL);
	map = init_map(*width, *height);
	if (!map)
		return (NULL);
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	return (map);
}

// Función principal que coordina la inicialización y lectura
t_map	*read_fdf(const char *filename)
{
	t_map	*map;
	int		fd;
	int		width;
	int		height;

	map = initialize_map(filename, &width, &height);
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		return (NULL);
	}
	if (!read_lines_to_map(fd, map, width, height))
	{
		free_map(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}
