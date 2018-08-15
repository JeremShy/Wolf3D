#include <wolf3d.h>

static void	get_ray(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, int x)
{
	double	col_pos;

	col_pos = 2. * x / (double)data->w - 1.; //  -1 <= col_pos <= 1
	ft_vec3_copy(ray_pos, data->cam_pos); // {0 <=> size_x, 0 <=> size_y}
	ft_vec3_init(ray_dir,
	(double[]){data->cam_dir[0] + data->cam_plane[0] * col_pos,
			data->cam_dir[1] + data->cam_plane[1] * col_pos, 0});
	printf("Direction :\n");
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
		printf("First x intersection : %d - %d\n", (int)first_x.collision_pos[0], (int)first_x.collision_pos[1]);
		printf("Ray pos : %f - %f\n", ray_pos[0], ray_pos[1]);
		first_x.corrected_dist = sqrt((first_x.collision_pos[0] - ray_pos[0]) * (first_x.collision_pos[0] - ray_pos[0]) + (first_x.collision_pos[1] - ray_pos[1]) * (first_x.collision_pos[1] - ray_pos[1]));
	}
	get_first_y(data, ray_pos, ray_dir, &first_y);
	if (first_x.error == 1 && first_y.error == 1)
	{
		printf("Error 32\n");
		exit(1);
		return ;
	}
	if (first_y.error != 1)
	{
		printf("First y intersection : %f - %f\n", first_y.collision_pos[0], first_y.collision_pos[1]);
		printf("Ray pos : %f - %f\n", ray_pos[0], ray_pos[1]);
		first_y.corrected_dist = sqrt((first_y.collision_pos[0] - ray_pos[0]) * (first_y.collision_pos[0] - ray_pos[0]) + (first_y.collision_pos[1] - ray_pos[1]) * (first_y.collision_pos[1] - ray_pos[1]));
	}
	else
	{
		printf("Y error !\n");
	}

	if (first_x.error == 0 && first_y.error == 1)
	{
		*ret = first_x;
	}
	else if (first_x.error == 1 && first_y.error == 0)
	{
		*ret = first_y;
	}
	else
	{
		printf("x distance : %f - y distance : %f\n", first_x.corrected_dist, first_y.corrected_dist);
		*ret = first_x.corrected_dist <= first_y.corrected_dist ? first_x : first_y;
	}

	/*

	if (side == 0)
		ret->corrected_dist = (map_pos[0] - ray_pos[0] + (int)(1 - (int)data->actual_step[0]) / 2) / ray_dir[0];
		// ret->corrected_dist = side_dist[0];
	else
		// ret->corrected_dist = side_dist[1];
		ret->corrected_dist = (map_pos[1] - ray_pos[1] + (1 - (int)data->actual_step[1]) / 2) / ray_dir[1];
		*/
}

static void	draw_col(t_data *data, t_hit_info *hit, int x)
{
	int	height;
	int	start;
	int	end;
	int	y;

	height = (int)fabs((data->h / hit->corrected_dist));
	printf("corrected_distance : %f\n", hit->corrected_dist);
	printf("Height : %d\n", height);
	start = (int)(-1. * height / 2. + data->h / 2.);
	end = (int)(height / 2. + data->h / 2.);

	if (start < 0)
		start = 0;
	if (end >= data->h)
		end = data->h - 1;
	y = 0;
	while (y < data->h)
	{
		if (y < start) // Partie haute
			put_pixel_to_image(data, 0x0000aa, x, y);
		else if (y >= start && y <= end) // Partie mediane
		{
			if (hit->side == 0)
				put_pixel_to_image(data, 0xFFFFFF, x, y);
			else
				put_pixel_to_image(data, 0xAA0000, x, y);
		}
		else // Partie basse
			put_pixel_to_image(data, 0xAAAAAA, x, y);
		y++;
	}
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
		printf("x = %d\n", x);
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
		|| data->going_left || data->going_right || data->rotating)
	{
		clear_image(data);
		data->must_refresh = 0;
		printf("Refreshing.\n");
		refresh_player(data);
		printf("Player position : %f %f\n", data->cam_pos[0], data->cam_pos[1]);
		render(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (1);
}
