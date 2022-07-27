/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:08:48 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/27 03:11:48 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

int	handle_keys(int key, fdf *info)
{
	ft_printf("%d\n", key);
	
	if (key == 100)
		info->map.offset_x += 10;
	else if (key == 97)
		info->map.offset_x -= 10;
	else if (key == 122)
		info->map.offset_y -= 10;
	else if (key == 115)
		info->map.offset_y += 10;
	else if (key == 65451)
		info->map.scale += 5;
	else if (key == 65453)
		info->map.scale -= 5;
	else if (key == 65430)
		info->map.angle -= 0.05;
	else if (key == 65432)
		info->map.angle += 0.05;
	mlx_clear_window(info->mlx, info->mlx_window);
	render_map(info);
	return (0);
}
