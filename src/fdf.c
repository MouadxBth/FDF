/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:20:00 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/22 06:20:47 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fdf.h"

static void	setup_event_hooks(t_fdf *info)
{
	mlx_key_hook(info->mlx_window, handle_exit, info);
	mlx_hook(info->mlx_window, 17, 0, cleanup, info);
	mlx_hook(info->mlx_window, 2, 1L << 0, handle_keys, info);
}

static void	initialize(t_fdf *info, char *map)
{
	if (!init_image(info) || !init_camera(&info->camera))
	{
		ft_printf("[ERROR]: Couldn't initialize!\n");
		cleanup(info);
	}
	if (!parse_map(&info->map, map))
	{
		ft_printf("[ERROR]: Invalid map!\n");
		cleanup(info);
	}
	if (!render_map(info))
	{
		ft_printf("[ERROR]: Couldn't render map!\n");
		cleanup(info);
	}
}

int	main(int argc, char **argv)
{
	t_fdf	info;

	if (!check_args(argc, argv))
		return (-1);
	if (!init_window(&info))
		return (-1);
	if (!init_map(&info.map, argv[1]))
		return (-1);
	initialize(&info, argv[1]);
	print_menu(&info, argv[1]);
	setup_event_hooks(&info);
	mlx_loop(info.mlx);
	cleanup(&info);
	return (0);
}
