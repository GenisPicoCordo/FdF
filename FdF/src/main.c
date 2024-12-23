/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:55:30 by gpico-co          #+#    #+#             */
/*   Updated: 2024/12/20 16:40:52 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t *)param);
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(800, 600, "Dibujo un píxel", true);
	if (!mlx)
	{
		ft_putstr_fd("Error al inicializar MLX42\n", 2);
		return (EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, 800, 600);
	if (!img)
	{
		ft_putstr_fd("Error al crear imagen\n", 2);
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	mlx_put_pixel(img, 400, 300, 0xFFFFFFFF);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, handle_key, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
