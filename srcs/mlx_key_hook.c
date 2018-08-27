#include <wolf3d.h>

int	key_press_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	ft_printf("Pressed key : %d\n", keycode);
	if (keycode == 53)
	{
		// free_dtab(data->map, data->size_y);
		free_mlx_and_exit(data);
	}
	if (!data->paused || keycode == 35)
	{
		if (keycode == 13) // W
			data->going_front = 1;
		else if (keycode == 1) // S
			data->going_back = 1;
		else if (keycode == 123) // A
		{
			data->rotating_left = 1;
			data->rotating_right = 0;
		}
		else if (keycode == 124) // D
		{
			data->rotating_left = 0;
			data->rotating_right = 1;
		}
		else if (keycode == 0) // Q
			data->going_left = 1;
		else if (keycode == 2) // E
			data->going_right = 1;
		else if (keycode == 35) // P
		{
			data->paused = (data->paused ? 0 : 1);
			data->going_front = 0;
			data->going_right = 0;
			data->going_left = 0;
			data->going_back = 0;
			data->rotating_right = 0;
			data->rotating_left = 0;
			data->must_refresh = 1;
		}
	}
	return (1);
}

int	key_release_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	ft_printf("released key : %d\n", keycode);
	if (keycode == 13) // W
		data->going_front = 0;
	else if (keycode == 1) // S
		data->going_back = 0;
	else if (keycode == 123) // A
		data->rotating_left = 0;
	else if (keycode == 124) // D
		data->rotating_right = 0;
	else if (keycode == 0) // Q
		data->going_left = 0;
	else if (keycode == 2) // E
		data->going_right = 0;
	return (1);
}
