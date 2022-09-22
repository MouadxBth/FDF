/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:06:58 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/22 06:36:07 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "fdf.h"

int	init_window(t_fdf *info)
{
	if (!info)
		return (error("Could not initialize window"));
	info->mlx = mlx_init();
	info->mlx_window = mlx_new_window(info->mlx, W_WIDTH, W_HEIGHT, "FDF");
	return (1);
}

int	init_image(t_fdf *info)
{
	if (!info)
		return (error("Could not initialize image"));
	info->image[0].id = mlx_new_image(info->mlx, W_WIDTH - (W_WIDTH / 5),
			W_HEIGHT);
	info->image[0].address = mlx_get_data_addr(info->image[0].id,
			&info->image[0].bits_per_pixel,
			&info->image[0].line_length,
			&info->image[0].endian);
	info->image[1].id = mlx_new_image(info->mlx, W_WIDTH - (W_WIDTH / 5),
			W_HEIGHT);
	info->image[1].address = mlx_get_data_addr(info->image[1].id,
			&info->image[1].bits_per_pixel,
			&info->image[1].line_length,
			&info->image[1].endian);
	info->c_img = 0;
	return (1);
}

static int	init_map_matrix(t_fdf_map *map)
{
	int	index;

	map->matrix = (t_point **)calloc(map->height, sizeof(t_point *));
	if (!map->matrix)
		return (error("Could not allocate enough memory for map matrix"));
	index = -1;
	while (++index < map->height)
	{
		map->matrix[index] = (t_point *)ft_calloc(map->width, sizeof(t_point));
		if (!map->matrix[index])
			return (error("Could not allocate enough memory for map matrix"));
	}
	return (1);
}

int	init_map(t_fdf_map *map, char *file)
{
	if (!map || !file)
		return (error("Could not initialize map"));
	if (!ft_map_size(map, file)
		|| map->width <= 0
		|| map->height <= 0)
		return (error("Could not open file or file is empty!"));
	map->scale = 4;
	map->x_offset = (W_WIDTH - (W_WIDTH / 5)
			- ((map->width / 2) * map->scale)) / 2;
	map->y_offset = (W_HEIGHT - ((map->height / 2) * map->scale)) / 2;
	map->z_max_orig = 1;
	map->z_min_orig = 1;
	map->z_max = 1;
	map->z_min = 0;
	map->colored = 0;
	return (init_map_matrix(map));
}

int	init_camera(t_camera *camera)
{
	if (!camera)
		return (error("Could not initialize camera"));
	camera->altitude = 1;
	camera->altitude_threshold = 10;
	camera->iso_projection = 1;
	camera->rotation_angle = 0.0;
	camera->iso_angle = M_PI_4;
	return (1);
}
