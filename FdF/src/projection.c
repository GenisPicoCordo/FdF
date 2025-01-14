/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:49:24 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/14 17:53:29 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	isometric_projection(int *x, int *y, int z)
{
	int	old_x;
	int	old_y;

	(void)z;
	old_x = *x;
	old_y = *y;
	*x = (int)((old_x - old_y) * 1);
	*y = (int)((old_x + old_y) * 1);
}
