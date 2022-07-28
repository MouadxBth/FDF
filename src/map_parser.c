/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:11:17 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 18:18:23 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static	void init_map(char *file, fdf_map *map)
{
	int	index;

	map->height = get_map_height(file);
	map->width = get_map_width(file);
	map->x_offset = 150;
	map->y_offset = 50;
	map->scale = 10;
	map->angle = 0.555;
	map->depth = 1;
	map->threshold = 10;
	map->alpha = 0.0;
	map->beta = 0.0;
	map->gamma = 0.0;
	map->matrix = (t_point **)malloc(sizeof(t_point) * (map->height * 1));
	if (!map->matrix)
		error("Could not allocate memeory for the map's matrix!");
	index = -1;
	while (++index <= map->height)
	{
		map->matrix[index] = (t_point *)malloc(sizeof(t_point) * (map->width + 1));
		if (!map->matrix[index])
			error("Could not allocate memeory for the map's matrix!");
	}
}

void	parse_map(char	*file, fdf *info)
{
	init_map(file, &info->map);
	fill_map_matrix(file, &info->map);
}
