/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:40:17 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/14 16:58:19 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// Función para manejar las teclas
void	handle_key(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx = (mlx_t *)param;
		mlx_close_window(mlx);
	}
}

// Inicializa MLX y la imagen
int	init_mlx(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(1920, 1080, "FdF Isometric Grid", true);
	if (!*mlx)
		return (0);
	*img = mlx_new_image(*mlx, 1920, 1080);
	if (!*img)
	{
		mlx_terminate(*mlx);
		return (0);
	}
	return (1);
}

// Carga el mapa desde el archivo .fdf
t_map	*load_map(const char *filename, mlx_t *mlx)
{
	t_map	*map;

	map = read_fdf(filename);
	if (!map)
	{
		printf("Error: No se pudo leer el archivo .fdf\n");
		mlx_terminate(mlx);
	}
	return (map);
}
