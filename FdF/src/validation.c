/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:30:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 17:39:07 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_error(const char *msg)
{
	ft_printf("Error: %s\n", msg);
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

int	check_extension(const char *file)
{
	const char	*extension = ".fdf";
	int			len_file;
	int			len_ext;

	len_file = ft_strlen(file);
	len_ext = ft_strlen(extension);
	if (len_file < len_ext)
		return (0);
	return (ft_strncmp(file + len_file - len_ext, extension, len_ext) == 0);
}

int	check_input(const char *file)
{
	int	fd;
	int	width;
	int	height;

	if (!check_extension(file))
	{
		ft_printf("Error: Invalid file extension. Expected '.fdf'.\n");
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	if (!count_lines_and_width(fd, &width, &height) \
		|| width <= 0 || height <= 0)
	{
		ft_printf("Error: Invalid map format.\n");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
