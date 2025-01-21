/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:31:30 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/21 18:47:09 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	is_pixel_in_bounds(int x, int y)
{
	return (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT);
}

uint32_t	get_color(int z, int min_z, int max_z)
{
	float	range;
	float	normalized_z;

	range = max_z - min_z;
	normalized_z = (z - min_z) / range;
	if (normalized_z < 0.1)
		return (COLOUR_ONE);
	else if (normalized_z < 0.2)
		return (COLOUR_TWO);
	else if (normalized_z < 0.3)
		return (COLOUR_THREE);
	else if (normalized_z < 0.4)
		return (COLOUR_FOUR);
	else if (normalized_z < 0.5)
		return (COLOUR_FIVE);
	else if (normalized_z < 0.6)
		return (COLOUR_SIX);
	else if (normalized_z < 0.7)
		return (COLOUR_SEVEN);
	else if (normalized_z < 0.8)
		return (COLOUR_EIGHT);
	else if (normalized_z < 0.9)
		return (COLOUR_NINE);
	else
		return (COLOUR_TEN);
}
