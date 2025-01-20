/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:16:23 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/20 12:30:54 by gpico-co         ###   ########.fr       */
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

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->height)
		free(map->z_values[i++]);
	free(map->z_values);
	free(map);
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
	return (1);
}

t_map	*read_fdf(const char *filename)
{
	t_map	*map;
	int		fd;
	int		width;
	int		height;

	if (!get_map_dimensions(filename, &width, &height))
		return (NULL);
	map = init_map(width, height);
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
