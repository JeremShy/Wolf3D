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
	ft_printf("size x : %d, size y : %d\n", data.size_x, data.size_y);
	if (!init_the_mlx(&data))
		return (0);
	clear_image(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);

	data.global_rotation_speed = 0.2;
	ft_vec3_init(data.cam_pos, (double[]){2, 5, 0});
	sync_map_squares(&data);
	print_map(&data);

	ft_vec3_init(data.cam_dir, (double[]){0, 1, 0});
	ft_vec3_init(data.cam_plane, (double[]){1, 0, 0});
	data.w = WIN_SIZE;
	data.h = WIN_SIZE;
	data.must_refresh = 1;

	// mlx_key_hook(data.win, &key_hook, &data);
	mlx_hook(data.win, 17, (1L << 17), red_cross_hook, &data);
	mlx_hook(data.win, 3, (1L << 1), key_release_hook, &data);
	mlx_hook(data.win, 2, (1L << 0), key_press_hook, &data);

	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
