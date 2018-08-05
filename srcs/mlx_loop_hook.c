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
	ft_vec3_print(data->cam_dir);
}

static void	init_step_and_side_dist(t_data *data, t_vec3 step, t_vec3 side_dist)
{
	int	mapx = (int)data->actual_ray_pos[0];
	int	mapy = (int)data->actual_ray_pos[1];
	if (data->actual_ray_dir[0] < 0) // Rayon vers la gauche
	{
		step[0] = -1;
		side_dist[0] = (data->actual_ray_pos[0] - mapx) * data->actual_delta_dist[0];
	}
	else
	{
		step[0] = 1;
		side_dist[0] = (mapx + 1.0 - data->actual_ray_pos[0]) * data->actual_delta_dist[0];
	}
		if (data->actual_ray_dir[1] < 0) // Rayon vers le haut
	{
		step[1] = -1;
		side_dist[1] = (data->actual_ray_pos[1] - mapy) * data->actual_delta_dist[1];
	}
	else // Rayon vers le bas
	{
		step[1] = 1;
		side_dist[1] = (mapy + 1.0 - data->actual_ray_pos[1]) * data->actual_delta_dist[1];
	}
}


static void	get_hit(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *ret)
{
	t_vec3	side_dist;
	int8_t	side;
	int	map_pos[2];
	int			hit;

	// ft_vec3_init(map_pos, (double[])
	// 	{(int)ray_pos[0], (int)ray_pos[1], 0});
	map_pos[0] = (int)ray_pos[0];
	map_pos[1] = (int)ray_pos[1];

	ft_vec3_init(data->actual_delta_dist, (double[]) // sqrt(1 + y^2 / x^ 2) ; sqrt(1 + x^2 / y^ 2)
		{fabs(1. / ray_dir[0]),
		fabs(1. / ray_dir[1]), 0});
	ft_vec3_copy(data->actual_ray_dir, ray_dir);
	ft_vec3_copy(data->actual_ray_pos, ray_pos);
	init_step_and_side_dist(data, data->actual_step, data->actual_side_dist);
	hit = 0;

	while (hit == 0)
	{
		if (side_dist[0] < side_dist[1]) // On a parcouru plus d'espace pour aller d'intersections horizontales en intersections horizontales que pour aller d'intersections verticales en intersections verticales
		{
			side_dist[0] = side_dist[0] + data->actual_delta_dist[0];
			map_pos[0] = map_pos[0] + (int)data->actual_step[0];
			side = 0;
		}
		else
		{
			side_dist[1] = side_dist[1] + data->actual_delta_dist[1];
			map_pos[1] = map_pos[1] + (int)data->actual_step[1];
			side = 1;
		}
		if (data->map[map_pos[1]][map_pos[0]] != 0)
			hit = 1;
	}
	printf("Wall detected at %d %d\n", map_pos[0], map_pos[1]);
	ret->side = side;
	// ft_vec3_copy(ret->collision_pos, map_pos);

	if (side == 0)
		ret->corrected_dist = (map_pos[0] - ray_pos[0] + (int)(1 - (int)data->actual_step[0]) / 2) / ray_dir[0];
		// ret->corrected_dist = side_dist[0];
	else
		// ret->corrected_dist = side_dist[1];
		ret->corrected_dist = (map_pos[1] - ray_pos[1] + (1 - (int)data->actual_step[1]) / 2) / ray_dir[1];
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
