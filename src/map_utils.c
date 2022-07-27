/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 18:37:50 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/27 19:13:00 by mbouthai         ###   ########.fr       */
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

static void	fill_map_matrix_line(int *line, char *str)
{
	 int	index;
	 char	**values;

	 if (!str || !line)
		 return ;
	 values = ft_split(str, ' ');
	 index = -1;
	 while (values[++index])
	 {
		 line[index] = ft_atoi(values[index]);
		 free(values[index]);
	 }
	 free(values);
}

void	fill_map_matrix(char *file, fdf_map *map)
{
	int	fd;
	int	index;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	index = 0;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		fill_map_matrix_line(map->matrix[index], line);
		if (line)
			index++;
		free(line);
	}
	map->matrix[index] = NULL;
	close(fd);
}
