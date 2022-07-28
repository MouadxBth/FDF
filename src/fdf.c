#include <mlx.h>
#include "fdf.h"

int	close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	error(char *msg)
{
	ft_printf("[Error]: %s\n", msg);
	exit(1);
}

static void	check_args(int argc, char **argv)
{
	char	**file;

	if (argc != 2)
		error("usage: ./fdf [map_name.fdf]");
	file = ft_split(argv[1], '.');
	if (!file)
		error("unknown file format");
	if (!file[1])
		error("unknown file format");
	if (ft_memcmp(file[1], "fdf", 3) != 0)
		error("unknown file format");
}

static void	initialize(fdf *info)
{
	info->mlx = mlx_init();
	info->mlx_window = mlx_new_window(info->mlx, 1000, 1000, "FDF");
	mlx_hook(info->mlx_window, 2, 0, handle_keys, info);
}

int	main(int argc, char **argv)
{
	fdf	info;

	check_args(argc, argv);

	initialize(&info);

	parse_map(argv[1], &info);

	render_map(&info);

	mlx_loop(info.mlx);
	return (0);
}
