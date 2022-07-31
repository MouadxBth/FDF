/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:20:00 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/31 03:12:53 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

static void	setup_event_hooks(t_fdf *info)
{
	mlx_hook(info->mlx_window, 2, 1L << 0, handle_keys, info);
}

int	main(int argc, char **argv)
{
	t_fdf	info;

	check_args(argc, argv);
	init_window(&info);
	init_map(&info.map, argv[1]);
	init_image(&info);
	init_camera(&info.camera);
	parse_map(&info.map, argv[1]);
	render_map(&info);
	mlx_put_image_to_window(info.mlx, info.mlx_window, info.image.id, 0, 0);
	setup_event_hooks(&info);
	mlx_loop(info.mlx);
	return (0);
}
