/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:53:18 by mbouthai          #+#    #+#             */
/*   Updated: 2022/08/20 01:13:21 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

static int	ft_lerp(int start, int end, float percentage)
{
	return ((int)(start + (end - start) * percentage));
}

static float	get_percentage(int start, int end, int current)
{
	float	placement;
	float	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

int	select_color(int max, int min, int z)
{
	float	percentage;
	int	value;

	percentage = get_percentage(min, max, z);
	if (percentage <= 0.0)
		return (mix_color(0, 255, 255, 255));
	if (percentage > 1.6)
		percentage = 1.6;
	value = 256 - (int)(percentage * 10) * 16;
	return (mix_color(0, 255, 125, value));
}

int	get_color(t_vector *line, t_point *current)
{
	int		red;
	int		green;
	int		blue;
	float	percentage;

	if (current->color == line->end.color)
		return (current->color);
	if (line->delta.x > line->delta.y)
		percentage = get_percentage(line->start.x, line->end.x, current->x);
	else
		percentage = get_percentage(line->start.y, line->end.y, current->y);
	red = ft_lerp(get_red(line->start.color),
			get_red(line->end.color),
			percentage);
	green = ft_lerp(get_green(line->start.color),
			get_green(line->end.color),
			percentage);
	blue = ft_lerp(get_blue(line->start.color),
			get_blue(line->end.color),
			percentage);
	return (mix_color(0, red, green, blue));
}
