#include <wolf3d.h>

int main()
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (!init_the_mlx(&data))
		return (0);
	clear_image(&data);
	put_pixel_to_image(&data, get_color_code(255, 0, 0), WIN_SIZE/2, WIN_SIZE/2);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop_hook(data.mlx, &loop_hook, &data);
	mlx_key_hook(data.win, &key_hook, &data);
	mlx_hook(data.win, 17, (1L << 17), red_cross_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
