#include <wolf3d.h>

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size_y)
	{
		j = 0;
		while (j < data->size_x)
		{
			if (i == (int)data->cam_pos[0] && j == (int)data->cam_pos[1])
				ft_putchar('p');
			else
				ft_putchar(data->map[i][j] + '0');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
