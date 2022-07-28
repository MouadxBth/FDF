/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:42:03 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 18:21:18 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "fdf.h"

float	ft_abs(float dx, float dy)
{
	float	max;

	if (dx > dy)
		max = dx;
	else
		max = dy;
	return (max);
}

float	fmodule(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}
void dda_1(t_point start, t_point end, fdf *info)
{
	int	color;
	color = 0xffffff;
	if (start.z || end.z)
		color = 0xe80c0c;
	project_point(&start, &info->map);
	project_point(&end, &info->map);
    int dx = end.x - start.x;
    int dy = end.y - start.y;
 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;
	
 
    for (int i = 0; i <= steps; i++)
    {
	mlx_pixel_put(info->mlx, info->mlx_window, start.x, start.y, color);
        start.x += Xinc;           // increment in x at each step
        start.y += Yinc;           // increment in y at each step
                             // generation step by step
    }
}

void	dda(t_point start, t_point end, fdf *info)
{
	float	dx;
	float	dy;
	float	max;
	int	color;
	
	color = 0xffffff;
	if (start.z >= info->map.threshold || end.z >= info->map.threshold)
		color = 0xe80c0c;
	project_point(&start, &info->map);
	project_point(&end, &info->map);
	dx = end.x - start.x;
	dy = end.y - start.y;
	max = fmax(fabs(dx), fabs(dy));
	dx /= max;
	dy /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		mlx_pixel_put(info->mlx, info->mlx_window, start.x, start.y, color);
		start.x += dx;
		start.y += dy;
	}
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
				dda(matrix[y][x], matrix[y][x + 1], info);
			if (y < info->map.height - 1)
				dda(matrix[y][x], matrix[y + 1][x], info);
			x++;
		}
		y++;
	}
}
