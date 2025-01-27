/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:24:53 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 16:04:48 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	validate_file_extension(char *file)
{
	const char	*extension = ".fdf";
	size_t		file_len;
	size_t		ext_len;

	file_len = ft_strlen(file);
	ext_len = ft_strlen(extension);
	if (file_len >= ext_len
		&& ft_strncmp(file + file_len - ext_len, extension, ext_len) == 0)
	{
		return (1);
	}
	return (0);
}

void	read_file_data(int fd, t_map *map)
{
	char	*line;
	int		row;

	row = 0;
	map->grid2d = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->grid2d)
	{
		print_error_message(ENOMEM);
	}
	map->grid2d[map->rows] = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->grid2d[row] = ft_strdup(line);
		free(line);
		row++;
		line = get_next_line(fd);
	}
	if (row == 0)
	{
		free_allocated_array((void **)map->grid2d);
		print_error_message(EBADF);
	}
}

int	count_lines_in_file(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

void	process_input_data(char **argv, t_map *map)
{
	int	fd;

	if (!validate_file_extension(argv[1]))
	{
		print_error_message(EINVAL);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		print_error_message(EBADF);
	}
	map->rows = count_lines_in_file(fd);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		print_error_message(EBADF);
	}
	read_file_data(fd, map);
	close(fd);
}
