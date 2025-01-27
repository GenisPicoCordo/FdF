/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:44 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/27 15:22:28 by gpico-co         ###   ########.fr       */
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

void	release_memory(t_map *map)
{
	int	i;

	if (map->grid3d)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->grid3d[i]);
			i++;
		}
		free(map->grid3d);
		map->grid3d = NULL;
	}
	if (map->fgrid)
	{
		i = 0;
		while (i < map->rows)
		{
			free(map->fgrid[i]);
			i++;
		}
		free(map->fgrid);
		map->fgrid = NULL;
	}
}

void	free_allocated_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_error_message(int error_code)
{
	errno = error_code;
	perror("Error detected");
	exit(EXIT_FAILURE);
}
