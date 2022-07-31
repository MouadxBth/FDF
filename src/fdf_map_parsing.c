/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_map_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 01:09:26 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/31 03:50:36 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static void	fill_map_matrix_row(t_point *matrix, char *str, int row)
{
	int		column;
	char	**values;

	if (!str || !matrix)
		return ;
	column = -1;
	values = ft_split(str, ' ');
	while (values[++column])
	{
		matrix[column].x = column;
		matrix[column].y = row;
		matrix[column].z = ft_atoi(values[column]);
		free(values[column]);
	}
	free(values);
}

void	parse_map(t_fdf_map *map, char *file)
{
	int		fd;
	int		row;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	row = 0;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		fill_map_matrix_row(map->matrix[row], line, row);
		if (line)
			row++;
		free(line);
	}
	map->matrix[row] = NULL;
	close(fd);
}
