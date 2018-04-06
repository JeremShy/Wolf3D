#include <wolf3d.h>

int		handle_error_void(void *variable, void *error_value, char *msg)
{
	if (variable == error_value)
	{
		ft_printf("%s\n", msg);
		return (1);
	}
	return (0);
}

void	free_dtab(int8_t **dtab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(dtab[i]);
		i++;
	}
	free(dtab);
}

void	sync_map_squares(t_data *data)
{
	data->cam_square[0] = (int)data->cam_pos[0];
	data->cam_square[1] = (int)data->cam_pos[1];
	data->cam_square[2] = (int)data->cam_pos[2];
}
