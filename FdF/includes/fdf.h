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

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <sys/stat.h>
# include "MLX42/MLX42.h"
# include "libft.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

# define COLOUR_ONE 0xFF5733ff
# define COLOUR_TWO 0xFFBD33ff
# define COLOUR_THREE 0xDBFF33ff
# define COLOUR_FOUR 0x75FF33ff
# define COLOUR_FIVE 0x33FF57ff
# define COLOUR_SIX 0x33FFBDff
# define COLOUR_SEVEN 0x33DBFFff
# define COLOUR_EIGHT 0x3375FFff
# define COLOUR_NINE 0x5733FFff
# define COLOUR_TEN 0xBD33FFff
# define DEFAULT_COLOR 0xFFFFFF

# define PI 3.14159265359

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	colour;
}	t_point;

typedef struct s_fpoint
{
	float	x;
	float	y;
	int		colour;
}	t_fpoint;

typedef struct s_delta
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	int		step_count;
}	t_delta;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			max;
	int			min;
	int			map_colour;
	float		scaling_factor;
	float		vertical_scale;
	float		projection_angle_alpha;
	float		projection_angle_beta;
	float		zoom_level;
	int			flat_projection_mode;
	int			default_color;
	int			width_offset;
	int			height_offset;
	char		**grid2d;
	t_point		**grid3d;
	t_fpoint	**fgrid;
}	t_map;

typedef struct s_fdf
{
	t_map		*map;
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_fdf;

// Function declarations
void	initialize_map(t_map *map);
void	release_memory(t_map *map);
void	free_allocated_array(void **array);
void	print_error_message(int error_code);

int		validate_file_extension(char *file);
int		count_lines_in_file(int fd);
void	read_file_data(int fd, t_map *map);
int		check_file_access(char *file);

void	allocate_grid_memory(t_map *map);
void	calculate_columns(t_map *map);
void	populate_columns(t_map *map, int row);
void	generate_matrix(t_map *map);

void	prepare_projection_data(t_map *map);
void	assign_color_to_point(t_map *map, int i, int j);

int		create_window_and_render(t_map *map);
void	handle_key_events(void *param);
void	handle_rotation_keys(void *param);

float	calculate_color_percentage(int max, int min, int current);
int		get_color_based_on_percentage(double percentage);
int		get_maximum(int a, int b);
int		get_minimum(int a, int b);

void	calculate_projection(t_map *map, int i, int j);
void	set_2d_projection_mode(t_map *map);

void	update_delta_values(t_delta *delta, t_fpoint start, t_fpoint end);
void	draw_line_segment(t_fdf *fdf, t_fpoint start, t_fpoint end);
void	connect_grid_points(t_fdf *fdf, int x, int y);

void	render_grid(void *param);
void	handle_all_hooks(void *param);

// Libft-based utility functions
int		is_valid_character(char c);
char	**split_line(const char *str, char delimiter);
int		convert_to_int(const char *str);
int		contains_comma(const char *str);
int		extract_color_from_line(const char *str);
void	process_input_data(char **argv, t_map *map);
void	validate_and_open_file(char *file, t_map *map, int *fd);
void	reset_image(t_fdf *fdf);
void	adjust_scaling_factor(t_map *map);

#endif
