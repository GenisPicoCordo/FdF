/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 17:32:54 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	setup_and_run(char *filename)
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;

	map = read_fdf(filename);
	if (!map)
	{
		ft_printf("Error loading map.\n");
		return (0);
	}
	if (!init_mlx(&mlx, &img))
	{
		free_map(map);
		ft_printf("Error initializing MLX.\n");
		return (0);
	}
	draw_isometric_grid(img, map, 540, 600);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, handle_key, mlx);
	mlx_loop(mlx);
	free_map(map);
	mlx_terminate(mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage: ./fdf <file.fdf>\n");
		return (EXIT_FAILURE);
	}
	if (!check_input(argv[1]))
		return (EXIT_FAILURE);
	if (!setup_and_run(argv[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
