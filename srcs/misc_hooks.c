#include <wolf3d.h>

int	red_cross_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	free_mlx_and_exit(data);
	return (0);
}
