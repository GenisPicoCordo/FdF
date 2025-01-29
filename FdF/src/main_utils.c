/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:04:22 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 12:46:39 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Initializes the map structure with default values for rendering 
// and scaling.
void	initialize_map(t_map *map)
{
	map->rows = 0;
	map->cols = 0;
	map->max = 0;
	map->min = 0;
	map->width_offset = WINDOW_WIDTH / 2;
	map->height_offset = WINDOW_HEIGHT / 4;
	map->scaling_factor = 6;
	map->vertical_scale = 0.1;
	map->projection_angle_alpha = 0.75;
	map->projection_angle_beta = 2.1;
	map->zoom_level = 1.2;
	map->flat_projection_mode = -1;
	map->map_colour = -1;
}

// Processes input data by validating, opening, 
// reading, and parsing the map file.
void	process_input_data(char **argv, t_map *map)
{
	int	fd;

	validate_and_open_file(argv[1], map, &fd);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error: Unable to reopen file.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	read_file_data(fd, map);
	if (parse_map(map))
	{
		ft_free(map->grid2d);
		exit(1);
	}
	close(fd);
}
