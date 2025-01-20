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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

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

typedef struct s_map
{
	int	**z_values;
	int	width;
	int	height;
}	t_map;

typedef struct s_step
{
	float	x_step;
	float	y_step;
	float	step;
}	t_step;

typedef struct s_draw_info
{
	mlx_image_t	*img;
	int			x;
	int			y;
	int			z0;
	int			z1;
}	t_draw_info;

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

// Prototipos de funciones main_utils
void	handle_key(mlx_key_data_t keydata, void *param);
int		init_mlx(mlx_t **mlx, mlx_image_t **img);

// Prototipos de funciones mapa
int		get_map_dimensions(const char *filename, int *width, int *height);
t_map	*init_map(int width, int height);
void	free_map(t_map *map);
int		read_lines_to_map(int fd, t_map *map, int width, int height);
t_map	*read_fdf(const char *filename);

// Prototipos de funciones map_utils
int		count_lines_and_width(int fd, int *width, int *height);
int		**allocate_z_values(int width, int height);
int		ft_count_words(const char *str);
int		process_line(char *line, t_map *map, int y, int width);

// Prototipos de funciones draw
void	set_line_points(t_line *line, t_draw_info *info, int is_horizontal);
void	draw_grid_line(t_draw_info *info, int is_horizontal);
void	set_info_values(t_draw_info *info, mlx_image_t *img, int x, int y);
void	draw_grid_segments(t_draw_info *info, t_map *map, int x, int y);
void	draw_isometric_grid(mlx_image_t *img, t_map *map);

// Prototipos de funciones draw_utils1
void	apply_isometric_projection(int *x, int *y, int z);
t_step	calculate_steps(t_line *line);
void	draw_pixels(mlx_image_t *img, t_line *line, \
	t_step *step, uint32_t color);
void	draw_line_basic(mlx_image_t *img, t_line *line, uint32_t color);
void	apply_transformations(t_line *line, t_draw_info *info);

// Prototipos de funciones draw_utils2
void	set_line_coordinates(t_draw_params *params, \
	t_line *line, int direction);
void	calculate_increments(t_line *line, float *inc_x, \
	float *inc_y, float *step);
void	set_z_values(t_draw_params *params, int direction, int *z0, int *z1);
int		is_pixel_in_bounds(int x, int y);

#endif
