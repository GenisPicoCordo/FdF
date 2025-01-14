/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:48:41 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/10 13:01:36 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Función para inicializar un nuevo mapa
static t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	map->z_values = NULL;
	return (map);
}

// Función para manejar errores de memoria o lectura
static t_map	*handle_error(t_map *map, int fd)
{
	if (fd >= 0)
		close(fd);
	if (map)
	{
		if (map->z_values)
			free(map->z_values);
		free(map);
	}
	return (NULL);
}

// Lógica principal del bucle para procesar líneas del archivo
static int	process_lines(int fd, t_map *map)
{
	char	*line;
	int		width;
	int		*z_row;

	line = get_next_line(fd);
	while (line)
	{
		z_row = process_line(line, &width);
		free(line);
		if (!z_row)
			return (0);
		map->z_values = resize_array(map->z_values, map->height, \
			map->height + 1);
		if (!map->z_values)
			return (0);
		map->z_values[map->height] = z_row;
		map->height++;
		map->width = width;
		line = get_next_line(fd);
	}
	return (1);
}

// Función principal para leer el archivo .fdf
t_map	*read_fdf(const char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: No se pudo abrir el archivo %s\n", filename);
		return (NULL);
	}
	map = init_map();
	if (!map)
		return (handle_error(NULL, fd));
	if (!process_lines(fd, map))
		return (handle_error(map, fd));
	close(fd);
	return (map);
}
