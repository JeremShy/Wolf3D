#include <wolf3d.h>

int	key_press_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	ft_printf("Pressed key : %d\n", keycode);
	if (keycode == 53)
	{
		free_dtab(data->map, data->size_y);
		free_mlx_and_exit(data);
	}
	if (keycode == 13 || keycode == 126) // W
		data->going_front = 1;
	else if (keycode == 1 || keycode == 125) // S
		data->going_back = 1;
	else if (keycode == 0 || keycode == 123) // A
	{
		data->rotating = 1;
		data->actual_rotation_speed = -1 * data->global_rotation_speed;
	}
	else if (keycode == 2 || keycode == 124) // D
	{
		data->rotating = 1;
		data->actual_rotation_speed = data->global_rotation_speed;
	}
	else if (keycode == 12) // Q
		data->going_left = 1;
	else if (keycode == 14) // D
		data->going_right = 1;
	return (1);
}

int	key_release_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	ft_printf("released key : %d\n", keycode);
	if (keycode == 13 || keycode == 126) // W
		data->going_front = 0;
	else if (keycode == 1 || keycode == 125) // S
		data->going_back = 0;
	else if (keycode == 0 || keycode == 123) // A
		data->rotating = 0;
	else if (keycode == 2 || keycode == 124) // D
		data->rotating = 0;
	else if (keycode == 12) // Q
		data->going_left = 0;
	else if (keycode == 14) // D
		data->going_right = 0;
	return (1);
}
