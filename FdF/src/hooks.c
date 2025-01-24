/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:33:03 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 12:10:25 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	handle_key_events(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->map->vertical_scale += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		if (fdf->map->vertical_scale >= 0.05)
			fdf->map->vertical_scale -= 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->height_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->height_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->width_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->width_offset += 5;
}

void	handle_rotation_keys(void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->map->zoom_level += 0.075;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		if (fdf->map->zoom_level >= 0)
			fdf->map->zoom_level -= 0.075;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		fdf->map->projection_angle_alpha += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		fdf->map->projection_angle_alpha -= 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
		fdf->map->projection_angle_alpha = 0.78;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		fdf->map->projection_angle_alpha = 1.57;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_T))
		fdf->map->projection_angle_alpha = 0.866;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_U))
		fdf->map->flat_projection_mode = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_I))
		fdf->map->flat_projection_mode = -1;
}
