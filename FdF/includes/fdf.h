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
# include <stdint.h>

//	Gradiente de colores
# define COLOUR_ONE     0xFF6F61ff   // Coral (tono cálido)
# define COLOUR_TWO     0xFFA177ff   // Melón (tono intermedio)
# define COLOUR_THREE   0xFFD166ff   // Amarillo claro (tono vibrante)
# define COLOUR_FOUR    0x6B5B95ff   // Lavanda (tono frío)
# define COLOUR_FIVE    0x88B04Bff   // Verde pera (tono natural)
# define COLOUR_SIX     0x92A8D1ff   // Azul pastel (tono suave)
# define COLOUR_SEVEN   0x955251ff   // Rojo terracota (tono cálido)
# define COLOUR_EIGHT   0xB565A7ff   // Rosa púrpura (tono vibrante)
# define COLOUR_NINE    0x009B77ff   // Verde esmeralda (tono fresco)
# define COLOUR_TEN     0xDD4124ff   // Rojo intenso (tono llamativo)
# define BACKGROUND_COLOR  0x2C2C2CFF  // Gris oscuro (fondo neutro)

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
	int	min_z;
	int	max_z;
	int	scale;
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
	int			offset_x;
	int			offset_y;
	int			window_width;
	int			window_height;
	int			scale;
	t_map		*map;
}	t_draw_info;

// Prototipos de funciones main_utils
void		handle_key(mlx_key_data_t keydata, void *param);
int			init_mlx(mlx_t **mlx, mlx_image_t **img);

// Prototipos de funciones mapa
int			get_map_dimensions(const char *filename, int *width, int *height);
t_map		*init_map(int width, int height);
void		free_map(t_map *map);
int			read_lines_to_map(int fd, t_map *map, int width, int height);
t_map		*read_fdf(const char *filename);
t_map		*initialize_map(const char *filename, int *width, int *height);

// Prototipos de funciones map_utils
int			count_lines_and_width(int fd, int *width, int *height);
int			**allocate_z_values(int width, int height);
int			ft_count_words(const char *str);
int			process_line(char *line, t_map *map, int y, int width);
void		scale_z_values(t_map *map);

// Prototipos de funciones draw
void		set_line_points(t_line *line, t_draw_info *info, int is_horizontal);
void		draw_grid_line(t_draw_info *info, \
	int is_horizontal, uint32_t color);
void		set_info_values(t_draw_info *info, mlx_image_t *img, int x, int y);
void		draw_grid_segments(t_draw_info *info, \
	t_map *map, int x, int y);
void		draw_isometric_grid(mlx_image_t *img, t_map *map, \
	int window_width, int window_height);

// Prototipos de funciones draw_utils1
void		apply_isometric_projection(int *x, int *y, int z);
t_step		calculate_steps(t_line *line);
void		draw_pixels(mlx_image_t *img, t_line *line, \
	t_step *step, uint32_t color);
void		draw_line_basic(mlx_image_t *img, t_line *line, uint32_t color);
void		apply_transformations(t_line *line, t_draw_info *info);

// Prototipos de funciones draw_utils2
int			is_pixel_in_bounds(int x, int y);
uint32_t	get_color(int z, int min_z, int max_z);

// Prototipos de funciones input_utils
int			check_extension(const char *file);
int			check_input(const char *file);
void		print_error(const char *msg);

#endif
