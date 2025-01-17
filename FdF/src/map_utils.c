/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:38:26 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 15:53:53 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != ' ' && *str != '\n' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if ((*str == ' ' || *str == '\n') && in_word)
			in_word = 0;
		str++;
	}
	return (count);
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

int	count_lines_and_width(int fd, int *width, int *height)
{
	char	*line;

	*height = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	*width = ft_count_words(line);
	free(line);
	(*height)++;
	line = get_next_line(fd);
	while (line)
	{
		(*height)++;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

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
