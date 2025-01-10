/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:56:32 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/10 10:18:44 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	*process_line(char *line, int *width)
{
	char	**values;
	int		*z_row;
	int		i;

	values = ft_split(line, ' ');
	*width = 0;
	while (values[*width])
		(*width)++;
	z_row = malloc(sizeof(int) * (*width));
	if (!z_row)
	{
		while (*values)
			free(*values++);
		free(values);
		return (NULL);
	}
	i = 0;
	while (i < *width)
	{
		z_row[i] = ft_atoi(values[i]);
		free(values[i]);
		i++;
	}
	free(values);
	return (z_row);
}

// Función para redimensionar manualmente el array de punteros
int	**resize_array(int **array, int old_size, int new_size)
{
	int	**new_array;
	int	i;

	new_array = malloc(sizeof(int *) * new_size);
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_array[i] = array[i];
		i++;
	}
	free(array);
	return (new_array);
}

// Inicializar la ventana gráfica y la imagen
int	init_graphics(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(800, 600, "FdF", true);
	if (!*mlx)
		return (0);
	*img = mlx_new_image(*mlx, 800, 600);
	if (!*img)
	{
		mlx_terminate(*mlx);
		return (0);
	}
	return (1);
}

// Liberar la memoria del mapa
void	free_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		free(map->z_values[y]);
		y++;
	}
	free(map->z_values);
	free(map);
}
