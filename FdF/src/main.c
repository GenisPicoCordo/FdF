/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 12:20:38 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf <file.fdf>\n");
		return (EXIT_FAILURE);
	}
	if (!init_mlx(&mlx, &img))
		return (EXIT_FAILURE);
	map = read_fdf(argv[1]);
	if (!map)
	{
		ft_printf("Error loading map file.\n");
		return (EXIT_FAILURE);
	}
	draw_isometric_grid(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, handle_key, mlx);
	mlx_loop(mlx);
	free_map(map);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
