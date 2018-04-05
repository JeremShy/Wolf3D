#include <wolf3d.h>

static void	render(t_data *data)
{
	//TODO : render
}

static void	refresh_player(t_data *data)
{
	//TODO : Move
}

int	loop_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (data->must_refresh || data->going_back || data->going_front
		|| data->going_left || data->going_right || data->rotating)
	{
		data->must_refresh = 0;
		refresh_player(data);
		render(data);
	}
	return (1);
}
