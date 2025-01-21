/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:38:26 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 19:03:57 by gpico-co         ###   ########.fr       */
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
	if (*width == 0)
		return (0);
	while (line)
	{
		if (ft_count_words(line) != *width)
		{
			free(line);
			return (0);
		}
		free(line);
		(*height)++;
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

void	scale_z_values(t_map *map)
{
	int		x;
	int		y;
	float	scale_factor;

	scale_factor = (map->width + map->height) / 2.0f;
	//hay que mirar aqui porq no maneja bien los numeros negativos
	if (map->max_z - map->min_z != 0)
		scale_factor /= (map->max_z - map->min_z);
	else
		scale_factor /= 1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->z_values[y][x] *= scale_factor;
			x++;
		}
		y++;
	}
}

int	process_line(char *line, t_map *map, int y, int width)
{
	char	**split_line;
	int		x;
	int		value;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (0);
	x = 0;
	while (split_line[x] && x < width)
	{
		value = ft_atoi(split_line[x]);
		map->z_values[y][x] = value;
		if (value < map->min_z)
			map->min_z = value;
		if (value > map->max_z)
			map->max_z = value;
		free(split_line[x]);
		x++;
	}
	while (split_line[x])
		free(split_line[x++]);
	free(split_line);
	return (1);
}
