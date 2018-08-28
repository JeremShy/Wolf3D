#include <wolf3d.h>

void	draw_map_square(t_data *data, t_vec3 minimap_start, t_vec3 minimap_end, int x, int y)
{
	t_vec3	square_size;
	int		x_pixel;
	int		y_pixel;

	ft_vec3_init(square_size, (double[]){
		(minimap_end[0] - minimap_start[0]) / data->size_x,
		(minimap_end[1] - minimap_start[1]) / data->size_y,
		0
	});
	x_pixel = x * square_size[0];
	while (x_pixel < (x + 1) * square_size[0])
	{
		y_pixel = y * square_size[1];
		while (y_pixel < (y + 1) * square_size[1])
		{
			put_pixel_to_image(data, 0xAAAAAA, x_pixel, y_pixel);
			y_pixel++;
		}
		x_pixel++;
	}
}

void	draw_minimap(t_data *data)
{
	t_vec3	minimap_start;
	t_vec3	minimap_end;
	int		x;
	int		y;

	ft_vec3_init(minimap_start, (double[]){0, 0, 0});
	ft_vec3_init(minimap_end, (double[]){data->w / 4, data->h / 4, 0});
	darken(data, .2, minimap_start, minimap_end);
	x = 0;
	while (x < data->size_x)
	{
		y = 0;
		while(y < data->size_y)
		{
			if (data->map[y][x].num != 0)
				draw_map_square(data, minimap_start, minimap_end, x, y);
			y++;
		}
		x++;
	}
	put_pixel_to_image(data, 0xAA0000, data->cam_pos[0] * data-> w / (minimap_end[0] - minimap_start[0]) + minimap_start[0], data->cam_pos[1] * data->h / (minimap_end[1] - minimap_start[1])+ minimap_start[1]);
}