/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:04:05 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 18:18:56 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"

void	isometric(t_point *point, float angle)
{
	float	x, y;

	x = point->x;
	y = point->y;
	point->x = (x - y) * cos(angle);
	point->y = (x + y) * sin(angle) - point->z;
}

void	rotate(t_point *point, fdf_map *map)
{
	rotate_x(point, map->alpha);
	rotate_y(point, map->beta);
	rotate_z(point, map->gamma);
}

void	depth(t_point *point, fdf_map *map)
{
	if (point->z >= map->threshold)
		point->z += map->depth;
}

void	project_point(t_point *point, fdf_map *map)
{
	scale_point(point, map->scale);
	rotate(point, map);
	depth(point, map);
	isometric(point, map->angle);
	offset_point(point, map->x_offset, map->y_offset);
}
