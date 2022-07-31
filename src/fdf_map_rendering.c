/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_rendering.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 01:23:48 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/31 14:21:14 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"

static void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	bresenham_low(t_vector *line, t_fdf *info, int color)
{
	int	decision;

	decision = (line->dy << 1) - line->dx;
	while (line->start.x <= line->end.x)
	{
		pixel_put(&info->image, line->start.x, line->start.y, color);
		//mlx_pixel_put(info->mlx, info->mlx_window, line->start.x, line->start.y, color);
		if (decision <= 0)
			decision += line->dy << 1;
		else
		{
			decision += (line->dy - line->dx) << 1;
			line->start.y += line->sy;
		}
		line->start.x++;
	}
}

static void	bresenham_high(t_vector *line, t_fdf *info, int color)
{
	int	decision;

	decision = (line->dx << 1) - line->dy;
	while (line->start.y <= line->end.y)
	{
		pixel_put(&info->image, line->start.x, line->start.y, color);
		//mlx_pixel_put(info->mlx, info->mlx_window, line->start.x, line->start.y, color);
		if (decision <= 0)
			decision += (line->dx << 1);
		else
		{
			decision += (line->dx - line->dy) << 1;
			line->start.x += line->sx;
		}
		line->start.y++;
	}
}

void	draw(t_vector *line, t_fdf *info)
{
	int	color;

	color = 0xffffff;
	if (line->start.z || line->end.z)
		color = 0xe80c0c;
	if (line->dy < line->dx)
	{
		if (line->start.x > line->end.x)
			bresenham_low(line, info, color);
		else
			bresenham_low(line, info, color);
	}
	else
	{
		if (line->start.y > line->end.y)
			bresenham_high(line, info, color);
		else
			bresenham_high(line, info, color);
	}
}

void	render_map(t_fdf *info)
{
	int		x;
	int		y;
	t_vector	right;
	t_vector	down;

	y = -1;
	while (++y < info->map.height)
	{
		x = -1;
		while (++x < info->map.width)
		{
			if (x < info->map.width - 1)
			{
				init_vector(&right, info->map.matrix[y][x],
						info->map.matrix[y][x + 1], info);
				draw(&right, info);
			}
			if (y < info->map.height - 1)
			{
				init_vector(&down, info->map.matrix[y][x],
						info->map.matrix[y + 1][x], info);
				draw(&down, info);
			}
		}
	}
	mlx_put_image_to_window(info->mlx, info->mlx_window, info->image.id, 0, 0);
}
