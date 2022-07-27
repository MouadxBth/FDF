/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:11:17 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/27 19:46:40 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static	void init_map_matrix(fdf_map *map)
{
	int	index;

	map->matrix = (int **)malloc(sizeof(int *) * (map->height + 1));
	if (!map->matrix)
		error("Could not allocate memeory for the map's matrix!");
	index = -1;
	while (++index <= map->height)
	{
		map->matrix[index] = (int *)malloc(sizeof(int) * (map->width + 1));
		if (!map->matrix[index])
			error("Could not allocate memeory for the map's matrix!");
	}
}

static	void init_map(char *file, fdf_map *map)
{
	map->height = get_map_height(file);
	map->width = get_map_width(file);
	map->offset_x = 150;
	map->offset_y = 50;
	map->scale = 10;
	map->angle = 0.555;
}

void	parse_map(char	*file, fdf *info)
{
	init_map(file, &info->map);
	init_map_matrix(&info->map);
	fill_map_matrix(file, &info->map);
}
