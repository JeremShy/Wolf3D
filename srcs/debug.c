#include <wolf3d.h>

void	print_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (y < data->size_y)
	{
		x = 0;
		while (x < data->size_x)
		{
			if (y != -1 && x == 0)
			{
				ft_printf("%02d: ", y);
			}
			if (y == -1 && x == 0)
				ft_printf("    ");
			if (y == -1)
				ft_printf("%c", x % 10 + '0');
			else if (y == (int)data->cam_pos[0] && x == (int)data->cam_pos[1])
				ft_putchar('p');
			else
				ft_putchar(data->map[y][x] + '0');
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}
