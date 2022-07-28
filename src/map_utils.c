/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:37:50 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 03:21:12 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

size_t	get_map_height(char *file)
{
	int	fd;
	size_t	height;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

size_t	get_map_width(char *file)
{
	int	fd;
	size_t	width;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	width = ft_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

static void	fill_map_matrix_line(t_point *matrix, char *str, int y)
{
	 int	x;
	 char	**values;

	 if (!str || !matrix)
		 return ;
	 values = ft_split(str, ' ');
	 x = -1;
	 while (values[++x])
	 {
		 matrix[x].x = x;
		 matrix[x].y = y;
		 matrix[x].z = ft_atoi(values[x]);
		 free(values[x]);
	 }
	 free(values);
}

void	fill_map_matrix(char *file, fdf_map *map)
{
	int	fd;
	int	y;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	line = "";
	y = 0;
	while (line)
	{
		line = get_next_line(fd);
		fill_map_matrix_line(map->matrix[y], line, y);
		if (line)
			y++;
		free(line);
	}
	map->matrix[y] = NULL;
	close(fd);
}
