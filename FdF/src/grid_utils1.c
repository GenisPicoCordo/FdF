/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:25:24 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/24 10:46:31 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	adjust_scaling_factor(t_map *map)
{
	int	interval_x;
	int	interval_y;

	interval_x = WINDOW_WIDTH / (map->cols * cosf(35));
	interval_y = WINDOW_HEIGHT / (map->rows * sinf(35));
	if (interval_x > interval_y)
		map->scaling_factor = -interval_y / 2;
	else
		map->scaling_factor = -interval_x / 2;
}

int	get_maximum(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	get_minimum(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

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
