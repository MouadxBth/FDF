/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:49:53 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/27 19:07:05 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"

# define ABS(X) ((X<0)?(-X):(X))

static void	bresenham_low(t_point *start, t_point *end, fdf *info, int color)
{
	int	dx, dy, p, yi;

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
	int	dx, dy, p, xi;

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

void	render_map(fdf *info)
{
	t_point start, right, down;
	
	start.y = 0;
	while (start.y < info->map.height)
	{
		start.x = 0;
		start.z = info->map.matrix[start.y][start.x];
		right.y = start.y;
		down.y = start.y + 1;
		while (start.x < info->map.width) 
		{
			right.x = start.x + 1;
			down.x = start.x;
			if (start.x < info->map.width - 1)
			{
				right.z = info->map.matrix[right.y][right.x];
				bresenham(start, right, info);
			}
			if (start.y < info->map.height - 1)
			{
				down.z = info->map.matrix[down.y][down.x];
				bresenham(start, down, info);
			}
			start.x++;
		}
		start.y++;
	}
}
