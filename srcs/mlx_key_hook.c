#include <wolf3d.h>

int	key_hook(int keycode, void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (keycode == 53)
		free_mlx_and_exit(data);
	return (1);
}
