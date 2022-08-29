/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_drawing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 00:11:05 by mbouthai          #+#    #+#             */
/*   Updated: 2022/08/20 00:19:10 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

static int	in_window(t_point *point)
{
	return ((point->x > 0 && point->x <= W_WIDTH - (W_WIDTH / 5))
		&& (point->y >= 0 && point->y <= W_HEIGHT));
}

static void	pixel_put(t_image *img, t_point *point, int color)
{
	int	step;

	step = (point->y * img->line_length
			+ point->x * (img->bits_per_pixel / 8));
	img->address[step] = color;
	img->address[++step] = color >> 8;
	img->address[++step] = color >> 16;
	img->address[++step] = color >> 24;
}

void	draw(t_vector *vector, t_fdf *info)
{
	int		error;
	t_point	current;

	current = vector->start;
	while (current.x != vector->end.x || current.y != vector->end.y)
	{
		if (in_window(&current))
			pixel_put(&info->image[info->c_img], &current,
				get_color(vector, &current));
		if (point_collision(&current, &vector->end))
			break ;
		error = vector->delta.z * 2;
		if (error >= vector->delta.y)
		{
			vector->delta.z += vector->delta.y;
			current.x += vector->x_direction;
		}
		if (error <= vector->delta.x)
		{
			vector->delta.z += vector->delta.x;
			current.y += vector->y_direction;
		}
	}
}
