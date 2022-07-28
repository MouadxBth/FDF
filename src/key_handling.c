/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:08:48 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 18:20:27 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

int	handle_keys(int key, fdf *info)
{
	ft_printf("%d\n", key);
	
	if (key == 100)
		info->map.x_offset += 10;
	else if (key == 97)
		info->map.x_offset -= 10;
	else if (key == 122)
		info->map.y_offset -= 10;
	else if (key == 115)
		info->map.y_offset += 10;
	else if (key == 65451)
		info->map.scale += 5;
	else if (key == 65453)
		info->map.scale -= 5;
	else if (key == 65430)
		info->map.angle -= 0.05;
	else if (key == 65432)
		info->map.angle += 0.05;
	else if (key == 65429)
		info->map.alpha += 0.05;
	else if (key == 65434)
		info->map.alpha -= 0.05;
	else if (key == 65436)
		info->map.beta += 0.05;
	else if (key == 65435)
		info->map.beta -= 0.05;
	else if (key == 65431)
		info->map.gamma += 0.05;
	else if (key == 65433)
		info->map.gamma -= 0.05;
	else if (key == 114)
		info->map.depth += 2;
	else if (key == 116)
		info->map.depth -= 2;
	else if (key == 'o')
		info->map.threshold += 1;
	else if (key == 'p')
		info->map.threshold -= 1;	
	mlx_clear_window(info->mlx, info->mlx_window);
	render_map(info);
	return (0);
}
