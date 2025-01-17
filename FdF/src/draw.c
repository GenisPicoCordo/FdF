/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpico-co <gpico-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:16:56 by gpico-co          #+#    #+#             */
/*   Updated: 2025/01/17 12:33:54 by gpico-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int is_pixel_in_bounds(int x, int y)
{
    return (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT);
}

void apply_isometric_projection(int *x, int *y, int z)
{
    double previous_x = *x;
    double previous_y = *y;
    
    // Ángulos para proyección isométrica (30° y 30°)
    double angle_x = 0.523599; // 30 grados en radianes
    double angle_y = 0.523599; // 30 grados en radianes
    
    // Aplicar transformación isométrica
    *x = (previous_x - previous_y) * cos(angle_x);
    *y = ((previous_x + previous_y) * sin(angle_y)) - z;
}

void draw_line_basic(mlx_image_t *img, t_line *line, uint32_t color)
{
    float step;
    float x_step;
    float y_step;
    float x = line->x0;
    float y = line->y0;
    int i = 0;

    // Calcular la diferencia más grande para los pasos
    float dx = line->x1 - line->x0;
    float dy = line->y1 - line->y0;
    step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    // Calcular incrementos
    x_step = dx / step;
    y_step = dy / step;

    // Dibujar la línea
    while (i <= step)
    {
        if (is_pixel_in_bounds((int)x, (int)y))
            mlx_put_pixel(img, (int)x, (int)y, color);
        x += x_step;
        y += y_step;
        i++;
    }
}

void draw_horizontal_lines(mlx_image_t *img, int x, int y, int spacing, int z0, int z1, int is_boundary)
{
    (void)spacing; // Se ignora porque no es utilizado actualmente
    (void)is_boundary; // Se ignora porque no es utilizado actualmente
    t_line line;
    int scale = 40;  // Factor de escala para hacer el dibujo más grande/pequeño
    int offset_x = 960;  // Centro de la pantalla
    int offset_y = 300;  // Ajustado para que se vea mejor

    // Configurar puntos iniciales
    line.x0 = x * scale;
    line.y0 = y * scale;
    line.x1 = (x + 1) * scale;
    line.y1 = y * scale;

    // Aplicar proyección isométrica
    apply_isometric_projection(&line.x0, &line.y0, z0 * scale / 8);
    apply_isometric_projection(&line.x1, &line.y1, z1 * scale / 8);

    // Aplicar offset
    line.x0 += offset_x;
    line.y0 += offset_y;
    line.x1 += offset_x;
    line.y1 += offset_y;

    // Dibujar línea
    draw_line_basic(img, &line, 0xFFFFFFFF);
}

void draw_vertical_lines(mlx_image_t *img, int x, int y, int spacing, int z0, int z1, int is_boundary)
{
    (void)spacing; // Se ignora porque no es utilizado actualmente
    (void)is_boundary; // Se ignora porque no es utilizado actualmente
    t_line line;
    int scale = 40;  // Factor de escala
    int offset_x = 960;  // Centro de la pantalla
    int offset_y = 300;  // Ajustado para que se vea mejor

    // Configurar puntos iniciales
    line.x0 = x * scale;
    line.y0 = y * scale;
    line.x1 = x * scale;
    line.y1 = (y + 1) * scale;

    // Aplicar proyección isométrica
    apply_isometric_projection(&line.x0, &line.y0, z0 * scale / 8);
    apply_isometric_projection(&line.x1, &line.y1, z1 * scale / 8);

    // Aplicar offset
    line.x0 += offset_x;
    line.y0 += offset_y;
    line.x1 += offset_x;
    line.y1 += offset_y;

    // Dibujar línea
    draw_line_basic(img, &line, 0xFFFFFFFF);
}

void draw_isometric_grid(mlx_image_t *img, t_map *map)
{
    int x, y;
    int spacing = 40;  // Espaciado entre puntos

    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (x < map->width - 1)
                draw_horizontal_lines(img, x, y, spacing, map->z_values[y][x], map->z_values[y][x + 1], 0);
            if (y < map->height - 1)
                draw_vertical_lines(img, x, y, spacing, map->z_values[y][x], map->z_values[y + 1][x], 0);
            x++;
        }
        y++;
    }
}