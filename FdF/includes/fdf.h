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
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

// Estructuras
typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	uint32_t	color;
}	t_line;

typedef struct s_vars
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_vars;

typedef struct s_map
{
	int	**z_values;
	int	width;
	int	height;
}	t_map;

// Nueva estructura para espaciado y offsets
typedef struct s_params
{
	int	spacing;
	int	offset_x;
	int	offset_y;
}	t_params;

// Estructura para agrupar los parámetros comunes de las líneas
typedef struct s_draw_params
{
	t_map		*map;
	t_params	*params;
}	t_draw_params;

// Estructura auxiliar para manejar los cálculos de Bresenham
typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_bresenham;

// Prototipos de funciones
void	draw_line_basic(mlx_image_t *img, t_line *line, uint32_t color);
void	isometric_projection(int *x, int *y, int z);
t_map	*read_fdf(const char *filename);
void	free_map(t_map *map);
int		*process_line(char *line, int *width);
int		**resize_array(int **array, int old_size, int new_size);
void	draw_line(mlx_image_t *img, t_line *line);
void	draw_grid(mlx_image_t *img, t_map *map);
void	init_bresenham(t_bresenham *b, t_line *line);
int		is_pixel_in_bounds(int x, int y);
void	handle_key(mlx_key_data_t keydata, void *param);
int		init_mlx(mlx_t **mlx, mlx_image_t **img);
t_map	*load_map(const char *filename, mlx_t *mlx);
void	calculate_spacing_and_offsets(t_map *map, t_params *params);
void	draw_grid_line(mlx_image_t *img, t_line *line, \
	t_map *map, t_params *params);
void	draw_grid_horizontal(mlx_image_t *img, \
	t_draw_params *draw_params, int x, int y);
void	draw_grid_vertical(mlx_image_t *img, \
	t_draw_params *draw_params, int x, int y);

#endif
