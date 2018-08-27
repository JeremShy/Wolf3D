#include <wolf3d.h>

static void	get_ray(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, int x)
{
	double	col_pos;

	col_pos = 2. * x / (double)data->w - 1.; //  -1 <= col_pos <= 1
	ft_vec3_copy(ray_pos, data->cam_pos); // {0 <=> size_x, 0 <=> size_y}
	ft_vec3_init(ray_dir,
	(double[]){data->cam_dir[0] + data->cam_plane[0] * col_pos,
			data->cam_dir[1] + data->cam_plane[1] * col_pos, 0});
	// printf("Direction :\n");
	ft_vec3_normalize(ray_dir);
	// ft_vec3_print(data->cam_dir);
}

static void	get_hit(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *ret)
{
	t_hit_info	first_x;
	t_hit_info	first_y;

	ft_bzero(&first_x, sizeof(t_hit_info));
	get_first_x(data, ray_pos, ray_dir, &first_x);
	if (first_x.error != 1)
	{
		first_x.corrected_dist = sqrt((first_x.collision_pos[0] - ray_pos[0]) * (first_x.collision_pos[0] - ray_pos[0]) + (first_x.collision_pos[1] - ray_pos[1]) * (first_x.collision_pos[1] - ray_pos[1]));
	}
	get_first_y(data, ray_pos, ray_dir, &first_y);
	if (first_x.error == 1 && first_y.error == 1)
	{
		ft_putstr_fd("Error : A ray hit no box, does the map have a hole ?\n", 2);
		exit(3);
		return ;
	}
	if (first_y.error != 1)
	{
		first_y.corrected_dist = sqrt((first_y.collision_pos[0] - ray_pos[0]) * (first_y.collision_pos[0] - ray_pos[0]) + (first_y.collision_pos[1] - ray_pos[1]) * (first_y.collision_pos[1] - ray_pos[1]));
	}

	if (first_x.error == 0 && first_y.error == 1)
		*ret = first_x;
	else if (first_x.error == 1 && first_y.error == 0)
		*ret = first_y;
	else
		*ret = first_x.corrected_dist < first_y.corrected_dist ? first_x : first_y;

	t_vec3 ab;
	t_vec3 look_dir;

	ft_vec3_init(ab, (double[]){ret->collision_pos[0] - ray_pos[0], ret->collision_pos[1] - ray_pos[1], 0});
	ft_vec3_copy(look_dir, data->cam_dir);
	ft_vec3_normalize(look_dir);
	ret->corrected_dist = ft_vec3_dot(ab, look_dir);
}

static void	render(t_data *data)
{
	int			x;
	t_vec3		ray_pos;
	t_vec3		ray_dir;
	t_hit_info	hit;

	x = 0;
	while (x < data->w)
	{
		// printf("x = %d\n", x);
		get_ray(data, ray_pos, ray_dir, x);
		get_hit(data, ray_pos, ray_dir, &hit);
		draw_col(data, &hit, x);
		x++;
	}
}

int	loop_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (data->must_refresh || data->going_back || data->going_front
		|| data->going_left || data->going_right || data->rotating_left || data->rotating_right)
	{
		data->must_refresh = 0;
		if (data->paused == 1)
		{
			darken(data, .2);
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
			mlx_string_put(data->mlx, data->win, data->w / 2, data->h / 4, 0xff0000, "PAUSED");
			return (1);
		}
		clear_image(data);
		refresh_player(data);
		// printf("Player position : %f %f\n", data->cam_pos[0], data->cam_pos[1]);
		render(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (1);
}
