/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:20:18 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 12:20:31 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_key(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t *)param);
}

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
