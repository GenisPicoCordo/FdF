/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:03 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/27 08:20:10 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	render_grid(void *param)
{
	t_fdf	*fdf;
	int		i;
	int		j;

	fdf = (t_fdf *)param;
	reset_image(fdf);
	if (fdf->map->flat_projection_mode == -1)
		prepare_projection_data(fdf->map);
	else
		set_2d_projection_mode(fdf->map);
	i = -1;
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			connect_grid_points(fdf, i, j);
		}
	}
}

void	handle_all_hooks(void *param)
{
	handle_key_events(param);
	handle_rotation_keys(param);
}

int	create_window_and_render(t_map *map)
{
	t_fdf	fdf;

	fdf.map = map;
	fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF Visualizer", true);
	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf.mlx || !fdf.img)
		return (EXIT_FAILURE);
	prepare_projection_data(fdf.map);
	render_grid(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_loop_hook(fdf.mlx, handle_all_hooks, &fdf);
	mlx_loop_hook(fdf.mlx, render_grid, &fdf);
	mlx_loop(fdf.mlx);
	mlx_delete_image(fdf.mlx, fdf.img);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
