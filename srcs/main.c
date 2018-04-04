#include <wolf3d.h>

int main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_printf("%s: usage: %s map\n", av[0], av[0]);
		return (1);
	}
	ft_bzero(&data, sizeof(data));
	data.av = av[0];
	if (!parse(&data, av[1]))
	{
		ft_printf("%s: parse error\n", av[0]);
		return (2);
	}
	print_map(&data);
	ft_printf("size x : %d, size y : %d\n", data.size_x, data.size_y);
	if (!init_the_mlx(&data))
		return (0);
	clear_image(&data);
	put_pixel_to_image(&data, get_color_code(255, 0, 0), WIN_SIZE/2, WIN_SIZE/2);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	mlx_key_hook(data.win, &key_hook, &data);
	mlx_hook(data.win, 17, (1L << 17), red_cross_hook, &data);

	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
