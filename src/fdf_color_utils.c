/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:38:58 by mbouthai          #+#    #+#             */
/*   Updated: 2022/08/19 23:27:13 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_transparency(int color)
{
	return ((color >> 24) & 0xff);
}

int	get_red(int color)
{
	return ((color >> 16) & 0xff);
}

int	get_green(int color)
{
	return ((color >> 8) & 0xff);
}

int	get_blue(int color)
{
	return (color & 0xff);
}

int	mix_color(int t, int r, int g, int b)
{
	if (t > 255)
		t = 255;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}
