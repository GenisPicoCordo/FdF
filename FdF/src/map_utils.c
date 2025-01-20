/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:38:26 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/20 12:31:41 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
