/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:30:16 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/29 12:58:25 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

//// Extracts the color from a string if it contains a hexadecimal 
// color code after a comma.
int	extract_color_from_line(const char *str)
{
	const char	*comma;
	int			color;

	comma = ft_strchr(str, ',');
	if (comma != NULL)
	{
		if (ft_strncmp(comma + 1, "0x", 2) == 0)
			color = ft_atoi_base(comma + 3, 16);
		else
			color = ft_atoi_base(comma + 1, 16);
		return (color);
	}
	return (0xFFFFFF);
}

// Calculates the relative position of a value within a 
// given range (min to max).
float	calculate_color_percentage(int max, int min, int current)
{
	double	placement;
	double	range;

	placement = current - min;
	range = max - min;
	if (range == 0)
		return (1.0);
	return (placement / range);
}

// Determines the corresponding color based on a percentage value.
int	get_color_based_on_percentage(double percentage)
{
	if (percentage < 0.05)
		return (COLOUR_ONE);
	if (percentage < 0.2)
		return (COLOUR_TWO);
	if (percentage < 0.3)
		return (COLOUR_THREE);
	if (percentage < 0.4)
		return (COLOUR_FOUR);
	if (percentage < 0.5)
		return (COLOUR_FIVE);
	if (percentage < 0.6)
		return (COLOUR_SIX);
	if (percentage < 0.7)
		return (COLOUR_SEVEN);
	if (percentage < 0.8)
		return (COLOUR_EIGHT);
	if (percentage < 0.9)
		return (COLOUR_NINE);
	return (COLOUR_TEN);
}

// Assigns a color to a point based on its height in the 3D grid.
void	assign_color_to_point(t_map *map, int i, int j)
{
	float	percentage;

	if (map->grid3d[i][j].colour != 0x00BCA1FF)
	{
		map->fgrid[i][j].colour = map->grid3d[i][j].colour;
	}
	else
	{
		percentage = calculate_color_percentage(map->max, \
			map->min, map->grid3d[i][j].z);
		map->fgrid[i][j].colour = get_color_based_on_percentage(percentage);
	}
}
