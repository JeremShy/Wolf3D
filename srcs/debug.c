#include <wolf3d.h>

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size_x)
	{
		j = 0;
		while (j < data->size_y)
		{
			ft_putchar(data->map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
