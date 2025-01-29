/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:24:53 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 12:51:54 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Checks if the given file has a valid ".fdf" extension.
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

// Verifies if the file exists, is accessible, and is a regular file.
int	check_file_access(char *file)
{
	struct stat	file_stat;
	int			result;

	result = 0;
	if (stat(file, &file_stat) != 0)
	{
		if (errno == ENOENT)
			ft_putendl_fd("Error: No such file or directory.", STDERR_FILENO);
		else if (errno == EACCES)
			ft_putendl_fd("Error: Permission denied.", STDERR_FILENO);
		else
			ft_putendl_fd("Error: Unable to access file.", STDERR_FILENO);
		result = -1;
	}
	else if (!S_ISREG(file_stat.st_mode))
	{
		ft_putendl_fd("Error: Not a regular file.", STDERR_FILENO);
		result = -1;
	}
	return (result);
}

// Counts the number of lines in the given file descriptor.
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

// Validates the file format, checks access 
// permissions, and determines the number of lines.
void	validate_and_open_file(char *file, t_map *map, int *fd)
{
	if (!validate_file_extension(file))
	{
		ft_putendl_fd("Error: Invalid file extension.\
			Expected .fdf.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (check_file_access(file) < 0)
		exit(EXIT_FAILURE);
	*fd = open(file, O_RDONLY);
	map->rows = count_lines_in_file(*fd);
	if (map->rows == 0)
	{
		ft_putendl_fd("Error: File is empty.", STDERR_FILENO);
		close(*fd);
		exit(EXIT_FAILURE);
	}
	close(*fd);
}

// Reads the file and stores its contents into a dynamically allocated 2D array.
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
		ft_putendl_fd("Error: File is empty.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}
