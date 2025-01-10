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

// Estructura para las coordenadas y el color de una línea
typedef struct s_line
{
	int			x0;
	int			y0;
	int			x1;
	int			y1;
	uint32_t	color;
}	t_line;

// Estructura para las variables de cálculo
typedef struct s_vars
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_vars;

// Estructura para guardar datos del mapa
typedef struct s_map
{
	int	**z_values;
	int	width;
	int	height;
}	t_map;

// Prototipos de funciones
void	handle_key(mlx_key_data_t keydata, void *param);
void	draw_line(mlx_image_t *img, t_line *line);
void	init_vars(t_vars *vars, t_line *line);
void	isometric_projection(int *x, int *y, int z);
t_map	*read_fdf(const char *filename);

// Prototipos de las funciones adicionales
int		*process_line(char *line, int *width);
int		**resize_array(int **array, int old_size, int new_size);
int		init_graphics(mlx_t **mlx, mlx_image_t **img);
void	free_map(t_map *map);
void	draw_map_lines(mlx_image_t *img, t_map *map);

#endif
