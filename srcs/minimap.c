#include <wolf3d.h>

void	draw_map_square(t_data *data, t_vec3 minimap_start, t_vec3 minimap_end, int row, int col)
{
	t_vec3	square_size;
	int		x_pixel;
	int		y_pixel;

	ft_vec3_init(square_size, (double[]){
		(minimap_end[1] - minimap_start[1]) / (double)data->size_x,
		(minimap_end[0] - minimap_start[0]) / (double)data->size_y,
		0
	});
	x_pixel = row * square_size[1];
	while (x_pixel < (row + 1) * square_size[1])
	{
		y_pixel = col * square_size[0];
		while (y_pixel < (col + 1) * square_size[0])
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
	int		row;
	int		col;
	t_vec3 player_pos;

	ft_vec3_init(minimap_start, (double[]){0, 0, 0});
	ft_vec3_init(minimap_end, (double[]){data->w / 4, data->h / 4, 0});
	darken(data, .2, minimap_start, minimap_end);
	row = 0;
	while (row < data->size_y)
	{
		col = 0;
		while(col < data->size_x)
		{
			if (data->map[row][col].num != 0)
				draw_map_square(data, minimap_start, minimap_end, row, col);
			col++;
		}
		row++;
	}

	// maths_to_screen(data, data->cam_pos, player_pos);
	ft_vec3_init(player_pos, (double[]){
		data->cam_pos[0] * data->w / data->size_y,
		data->cam_pos[1] * data->h / data->size_x,
	});
	printf("player_pos : {%f, %f}\n", player_pos[0], player_pos[1]);
	put_pixel_to_image(data, 0xFF0000,
		player_pos[0] * (minimap_end[0] - minimap_start[0]) / data->w,
		player_pos[1] * (minimap_end[1] - minimap_start[1]) / data->h);
}