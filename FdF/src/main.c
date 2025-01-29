/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 10:04:47 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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
