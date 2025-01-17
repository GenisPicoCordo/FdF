/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:51:36 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/10 10:29:15 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdlib.h>

// Estructuras
typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	uint32_t	color;
}	t_line;

typedef struct s_draw_params
{
	int			x;
	int			y;
	int			spacing;
	int			offset_x;
	int			offset_y;
	int			is_boundary;
	mlx_image_t	*img;
}	t_draw_params;

typedef struct s_map
{
	int	**z_values;
	int	width;
	int	height;
}	t_map;

// Prototipos de funciones para el manejo del mapa
t_map	*read_fdf(const char *filename);
void	free_map(t_map *map);
// Prototipos de funciones principales
void	draw_isometric_grid(mlx_image_t *img, t_map *map);
// Prototipos de funciones auxiliares
void	draw_horizontal_lines(mlx_image_t *img, int x, int y, int spacing, int z0, int z1, int is_boundary);
void	draw_vertical_lines(mlx_image_t *img, int x, int y, int spacing, int z0, int z1, int is_boundary);

// Prototipos de funciones main_utils
void	handle_key(mlx_key_data_t keydata, void *param);
int		init_mlx(mlx_t **mlx, mlx_image_t **img);
// Prototipos de funciones mapa
int		**allocate_z_values(int width, int height);
int		process_line(char *line, t_map *map, int y, int width);
int		read_lines_to_map(int fd, t_map *map, int width, int height);
int		ft_count_words(const char *str);
t_map	*init_map(int width, int height);
int		count_lines_and_width(int fd, int *width, int *height);
int		get_map_dimensions(const char *filename, int *width, int *height);

// Prototipos de funciones adicionales
void	draw_line(t_draw_params *params, t_line *line);
void	setup_line(t_draw_params *params, t_line *line, int direction);
void	apply_isometric_projection(int *x, int *y, int z);
int		is_pixel_in_bounds(int x, int y);
int		init_mlx(mlx_t **mlx, mlx_image_t **img);
int		ft_count_words(const char *str);

#endif
