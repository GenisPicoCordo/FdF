/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:16:23 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 15:53:28 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	**allocate_z_values(int width, int height)
{
	int	**z_values;
	int	i;

	z_values = malloc(sizeof(int *) * height);
	if (!z_values)
		return (NULL);
	i = 0;
	while (i < height)
	{
		z_values[i] = malloc(sizeof(int) * width);
		if (!z_values[i])
		{
			while (--i >= 0)
				free(z_values[i]);
			free(z_values);
			return (NULL);
		}
		i++;
	}
	return (z_values);
}

int	process_line(char *line, t_map *map, int y, int width)
{
	char	**split_line;
	int		x;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (0);
	x = 0;
	while (split_line[x] && x < width)
	{
		map->z_values[y][x] = ft_atoi(split_line[x]);
		free(split_line[x]);
		x++;
	}
	while (split_line[x])
		free(split_line[x++]);
	free(split_line);
	return (1);
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
