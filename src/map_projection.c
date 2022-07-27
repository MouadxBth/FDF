/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:04:05 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/27 20:02:47 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"
# define PI 3.14

void	isometric(t_point *point, float angle)
{
	int	x, y;

	x = point->x;
	y = point->y;
	point->x = (x - y) * cos(angle);
	point->y = (x + y) * sin(angle) - point->z;
}

void	project_point(t_point *point, fdf_map *map)
{
	scale_point(point, map->scale);
	isometric(point, map->angle);
	offset_point(point, map->offset_x, map->offset_y);
}
