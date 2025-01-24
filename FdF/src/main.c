/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 11:09:24 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
	map->flat_projection_mode = 0;
	map->default_color = -1;
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		render_status;

	if (argc != 2)
	{
		print_error_message(EINVAL);
		return (EXIT_FAILURE);
	}
	initialize_map(&map);
	process_input_data(argv, &map);
	generate_matrix(&map);
	free_allocated_array((void **)map.grid2d);
	render_status = create_window_and_render(&map);
	if (!render_status)
	{
		release_memory(&map);
		return (EXIT_FAILURE);
	}
	release_memory(&map);
	return (EXIT_SUCCESS);
}
