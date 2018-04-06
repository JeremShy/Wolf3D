#include <wolf3d.h>

static void	refresh_player(t_data *data)
{
	//TODO : Move
	(void)data;
}

static void	get_ray(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, double x)
{
	double	col_pos;

	col_pos = (2 * x / data->w) - 1; //  -1 <= col_pos <= 1

	ft_vec3_copy(ray_pos, data->cam_pos); // {0 <=> size_x, 0 <=> size_y}
	ft_vec3_init(ray_dir,
	(double[]){data->cam_dir[0] + data->cam_plane[0] * col_pos,
			data->cam_dir[1] + data->cam_plane[1] * col_pos, 0});
}

static void	init_step_from_ray(t_data *data, t_vec3 ray_dir, t_vec3 step, t_vec3)
{
	if (ray_dir[0] < 0) // Rayon vers la gauche
		step[0] = -1;
}

static void	get_hit(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir)
{
	t_vec3	side_dist;
	t_vec3	step;
	int8_t	hit;

	ft_vec3_init(side_dist, (double[]){0, 0, 0});
	ft_vec3_init(step, (double[]){0, 0, 0});
}

static void	render(t_data *data)
{
	double	x;
	t_vec3	ray_pos;
	t_vec3	ray_dir;
	double	y;
	
	x = 0;
	y = 0;
	while (x < data->w)
	{
		get_ray(data, ray_pos, ray_dir, x);
		x++;
	}
}

int	loop_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	data->must_refresh = 0;
	if (data->must_refresh || data->going_back || data->going_front
		|| data->going_left || data->going_right || data->rotating)
	{
		clear_image(data);
		data->must_refresh = 0;
		printf("Refreshing.\n");
		refresh_player(data);
		render(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (1);
}
