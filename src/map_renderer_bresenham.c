/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer_bresenham.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:49:53 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 04:27:21 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"

# define ABS(X) ((X<0)?(-X):(X))

static void	bresenham_low(t_point *start, t_point *end, fdf *info, int color)
{
	float	dx, dy, p, yi;

	dx = end->x - start->x;
	dy = end->y - start->y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy *= -1;
	}
	p = (2 * dy) - dx;
	while (start->x <= end->x)
	{
		mlx_pixel_put(info->mlx, info->mlx_window, start->x, start->y, color);
		if (p <= 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * (dy - dx));
			start->y += yi;
		}
		start->x++;
	}
}

static void	bresenham_high(t_point *start, t_point *end, fdf *info, int color)
{
	float	dx, dy, p, xi;

	dx = end->x - start->x;
	dy = end->y - start->y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx *= -1;
	}
	p = (2 * dx) - dy;
	while (start->y <= end->y)
	{
		mlx_pixel_put(info->mlx, info->mlx_window, start->x, start->y, color);
		if (p <= 0)
			p = p + (2 * dx);
		else
		{
			p = p + (2 * (dx - dy));
			start->x += xi;
		}
		start->y++;
	}
}


void	bresenham(t_point start, t_point end, fdf *info)
{
	int	color;

	color = 0xffffff;
	if (start.z || end.z)
		color = 0xe80c0c;
	project_point(&start, &info->map);
	project_point(&end, &info->map);

	if (ABS(end.y - start.y) < ABS(end.x - start.x))
	{
		if (start.x > end.x)
			bresenham_low(&end, &start, info, color);
		else
			bresenham_low(&start, &end, info, color);
	}
	else
	{
		if (start.y > end.y)
			bresenham_high(&end, &start, info, color);
		else
			bresenham_high(&start, &end, info, color);
	}
}

static void plotPixel(t_point start, t_point end, fdf *info)
{
    int pk = 2 * dy - dx;
    for (int i = 0; i < dx; i++)
    {
        x1 < x2 ? x1++ : x1--;
        if (pk < 0)
        {
            if (decide == 0)
            {
		printf("X: %d Y: %d\n", x1, y1);
                pk = pk + 2 * dy;
            }
            else
            {
		printf("X: %d Y: %d\n", y1, x1);
                pk = pk + 2 * dy;
            }
        }
        else
        {
            y1 < y2 ? y1++ : y1--;
            if (decide == 0)
		printf("X: %d Y: %d\n", x1, y1);
            else
		printf("X: %d Y: %d\n", y1, x1);
            pk = pk + 2 * dy - 2 * dx;
        }
    }
}

void	bresenham(int x, int y, int x1, int y1)
{
	int dx, dy;
	dx = abs(x1 - x);
	dy = abs(y1 - y);
    	if (dx > dy)
       		plotPixel(x, y, x1, y1, dx, dy, 0);
    	else
       		plotPixel(y, x, y1, x1, dy, dx, 1);
}

void	render_map(fdf *info)
{
	int	x, y;
	t_point	**matrix;

	if (!info)
		error("Passed an invalid info");
	matrix = info->map.matrix;
	y = 0;
	while (y < info->map.height)
	{
		x = 0;
		while (x < info->map.width)
		{
			if (x < info->map.width - 1)
				bresenham(matrix[y][x], matrix[y][x + 1], info);
			if (y < info->map.height - 1)
				bresenham(matrix[y][x], matrix[y + 1][x], info);
			x++;
		}
		y++;
	}
}
