/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 01:09:26 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/22 01:16:31 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static int	ft_get_height(t_point *point, char *str)
{
	char	**elements;

	if (!str)
		return (0);
	if (ft_str_ncontains(',', 1, str))
	{
		elements = ft_split(str, ',');
		point->z = ft_atoi(elements[0]);
		point->color = ft_hex_to_int(elements[1]);
		free(elements[1]);
		free(elements[0]);
		free(elements);
		return (1);
	}
	else
	{
		point->z = ft_atoi(str);
		point->color = 0xFFFFFF;
		return (0);
	}
	return (0);
}

static int	ft_free_elements(char **elements)
{
	int	index;

	if (!elements)
		return (0);
	index = -1;
	while (elements[++index])
		free(elements[index]);
	free(elements);
	return (0);
}

static void	ft_z_orig(t_fdf_map *map, int row, int column)
{
	if (map->matrix[row][column].z > map->z_max_orig)
		map->z_max_orig = map->matrix[row][column].z;
	else if (map->matrix[row][column].z < map->z_min_orig)
		map->z_min_orig = map->matrix[row][column].z;
}

static int	fill_map_matrix_row(t_fdf_map *map, char *str, int row)
{
	int		column;
	char	**values;

	if (!str || !map)
		return (1);
	column = -1;
	values = ft_split(str, ' ');
	if (ft_count_words(values) < map->width)
		return (ft_free_elements(values));
	while (++column < map->width && values[column])
	{
		map->matrix[row][column].x = column;
		map->matrix[row][column].y = row;
		if (ft_get_height(&map->matrix[row][column], values[column])
			&& !map->colored)
			map->colored = 1;
		ft_z_orig(map, row, column);
		free(values[column]);
	}
	if (values[column])
		free(values[column]);
	free(values);
	return (1);
}

int	parse_map(t_fdf_map *map, char *file)
{
	int		fd;
	int		row;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	row = 0;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (!fill_map_matrix_row(map, line, row))
		{
			free(line);
			return (0);
		}
		if (line)
			row++;
		free(line);
	}
	map->z_max = map->z_max_orig * map->scale;
	map->z_min = map->z_min_orig * map->scale;
	close(fd);
	return (1);
}
