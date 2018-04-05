#include <wolf3d.h>

static void	refresh_player(t_data *data)
{
	//TODO : Move
}

static void	render(t_data *data)
{
	double	x;
	double	y;
	
	x = 0;
	y = 0;
	while (x <= data->w)
	{
		x++;
	}
}

int	loop_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (data->must_refresh || data->going_back || data->going_front
		|| data->going_left || data->going_right || data->rotating)
	{
		data->must_refresh = 0;
		printf("Refreshing.\n");
		refresh_player(data);
		render(data);
	}
	return (1);
}
