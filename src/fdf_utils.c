/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:05:28 by mbouthai          #+#    #+#             */
/*   Updated: 2022/09/22 01:14:21 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <mlx.h>
#include "fdf.h"

int	error(char *msg)
{
	if (msg)
		ft_printf("[ERROR]: %s\n", msg);
	return (0);
}

int	check_args(int argc, char **argv)
{
	char	**file;
	int		index;

	if (argc != 2)
		return (error("usage: ./fdf [map_name.fdf]"));
	file = ft_split(argv[1], '.');
	if (!file)
		return (error("unknown file format"));
	if (!file[1])
		return (error("unknown file format"));
	if (ft_memcmp(file[1], "fdf", 3) != 0)
		return (error("unknown file format"));
	index = -1;
	while (file[++index])
		free(file[index]);
	free(file);
	return (1);
}

int	ft_count_words(char **elements)
{
	int	result;

	if (!elements)
		return (0);
	result = 0;
	while (elements[result] && *elements[result] != '\n')
		result++;
	return (result);
}

int	ft_map_size(t_fdf_map *map, char *file)
{
	int		fd;
	int		index;
	char	*line;
	char	**elements;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	elements = ft_split(line, ' ');
	map->width = ft_count_words(elements);
	map->height = 0;
	index = -1;
	while (elements[++index])
		free(elements[index]);
	free(elements);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (1);
}
