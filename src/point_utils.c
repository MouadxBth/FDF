/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:55:23 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 03:16:52 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

void	scale_point(t_point *point, int scale)
{
	point->x *= scale;
	point->y *= scale;
}

void	offset_point(t_point *point, int x_offset, int y_offset)
{
	point->x += x_offset;
	point->y += y_offset;
}

void	rotate_x(t_point *point, float angle)
{
	float y;

	y = point->y;
	point->y = y * cos(angle) + point->z * sin(angle);
	point->z = -y * sin(angle) + point->z * cos(angle);
}

void	rotate_y(t_point *point, float angle)
{
	float x;

	x = point->x;
	point->x = x * cos(angle) + point->z * sin(angle);
	point->z = -x * sin(angle) + point->z * cos(angle);
}

void	rotate_z(t_point *point, float angle)
{
	float x;
	float y;

	x = point->x;
	y = point->y;
	point->x = x * cos(angle) - y * sin(angle);
	point->y = x * sin(angle) + y * cos(angle);
}
