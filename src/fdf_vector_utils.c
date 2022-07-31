/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_vector_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 01:43:33 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/31 03:58:11 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	vector_start_is_end(t_vector *vector)
{
	return (vector->start.x == vector->end.x &&
		vector->start.y == vector->end.y);
}

void	init_vector(t_vector *vector, t_point start, t_point end, t_fdf *info)
{
	vector->start = start;
	vector->end = end;
	project_point(&vector->start, info);
	project_point(&vector->end, info);
	vector->dx = ft_abs(end.x - start.x);
	vector->dy = ft_abs(end.y - start.y);
	if (start.x <= end.x)
		vector->sx = 1;
	else
		vector->sx = -1;
	if (start.y <= end.y)
		vector->sy = 1;
	else
		vector->sy = -1;
	vector->error = vector->dx + vector->dy;
}
