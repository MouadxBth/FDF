/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:06:24 by mbouthai          #+#    #+#             */
/*   Updated: 2022/07/28 18:18:03 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct
{
	int	width;
	int	height;
	int	scale;
	int	x_offset;
	int	y_offset;
	int	depth;
	int	threshold;
	float	alpha;
	float	beta;
	float	gamma;
	float	angle;
	t_point	**matrix;
}	fdf_map;

typedef struct
{
	void	*mlx;
	void	*mlx_window;
	fdf_map	map;
}	fdf;

void	error(char *msg);

size_t	get_map_width(char *file);
size_t	get_map_height(char *file);
void	fill_map_matrix(char *file, fdf_map *map);

void	parse_map(char *file, fdf *info);

void	scale_point(t_point *point, int scale);
void	offset_point(t_point *point, int offset_x, int offset_y);
void	rotate_x(t_point *point, float angle);
void	rotate_y(t_point *point, float angle);
void	rotate_z(t_point *point, float angle);

void	isometric(t_point *point, float angle);
void	project_point(t_point *point, fdf_map *map);

void	render_map(fdf *info);
int	handle_keys(int key, fdf *info);

#endif
