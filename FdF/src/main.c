/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/10 10:18:36 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t *)param);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;

	if (argc != 2)
	{
		printf("Usage: ./fdf <file.fdf>\n");
		return (EXIT_FAILURE);
	}
	if (!init_graphics(&mlx, &img))
		return (EXIT_FAILURE);
	map = read_fdf(argv[1]);
	if (!map)
	{
		printf("Error: No se pudo leer el archivo .fdf\n");
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	draw_map_lines(img, map);
	free_map(map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, handle_key, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
