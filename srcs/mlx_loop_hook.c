#include <wolf3d.h>


// The player has to move depending of his direction
/*
	if direction is {-1, 0} and the player is going front
	 The player has to move of {-MOVEMENT_SPEED, 0}

	if (direction is {-1, 0}) and the player is going going_left
		the player has to move of {0, -MOVEMENT_SPEED}
*/


static void	refresh_player(t_data *data)
{
	//TODO : Move
	t_vec3 move_vector;

	ft_vec3_init(move_vector, (double[3]){0, 0, 0});
	if (data->going_front)
	{
		move_vector[0] = MOVEMENT_SPEED * data->cam_dir[0];
		move_vector[1] = MOVEMENT_SPEED * data->cam_dir[1];
	}
	else if (data->going_back)
	{
		move_vector[0] =  -1 * MOVEMENT_SPEED * data->cam_dir[0];
		move_vector[1] =  -1 * MOVEMENT_SPEED * data->cam_dir[1];
	}
	if (data->going_left)
	{
		move_vector[0] = MOVEMENT_SPEED * data->cam_dir[1];
		move_vector[1] = MOVEMENT_SPEED * data->cam_dir[0];
	}
	else if (data->going_right)
	{
		move_vector[0] =  -1 * MOVEMENT_SPEED * data->cam_dir[1];
		move_vector[1] =  -1 * MOVEMENT_SPEED * data->cam_dir[0];
	}
	ft_vec3_add(data->cam_pos, data->cam_pos, move_vector);
	printf("new pos : \n");
	ft_vec3_print(data->cam_pos);
	// if (data->)
}

static void	get_ray(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, double x)
{
	double	col_pos;

	col_pos = 2 * (x / data->w) - 1; //  -1 <= col_pos <= 1

	ft_vec3_copy(ray_pos, data->cam_pos); // {0 <=> size_x, 0 <=> size_y}
	ft_vec3_init(ray_dir,
	(double[]){data->cam_dir[0] + data->cam_plane[0] * col_pos,
			data->cam_dir[1] + data->cam_plane[1] * col_pos, 0});
}

static void	init_step_and_side_dist(t_data *data, t_vec3 step, t_vec3 side_dist)
{
	if (data->actual_ray_dir[0] < 0) // Rayon vers la gauche
	{
		step[0] = -1.0;
		side_dist[0] = (data->actual_ray_pos[0] - (int)data->actual_ray_pos[0]) * data->actual_delta_dist[0];
	}
	else
	{
		step[0] = 1.0;
		side_dist[0] = ((double)(int)(data->actual_ray_pos[0]) + 1.0 - data->actual_ray_pos[0]) * data->actual_delta_dist[0];
	}
	if (data->actual_ray_dir[1] < 0) // Rayon vers la gauche
	{
		step[1] = -1.0;
		side_dist[1] = (data->actual_ray_pos[1] - (int)data->actual_ray_pos[1]) * data->actual_delta_dist[1];
	}
	else
	{
		step[1] = 1.0;
		side_dist[1] = ((double)(int)(data->actual_ray_pos[1]) + 1.0 - data->actual_ray_pos[1]) * data->actual_delta_dist[1];
	}
}



static void	get_hit(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *ret)
{
	t_vec3	side_dist;
	int8_t	side;
	t_vec3	map_pos;

	ft_vec3_init(data->actual_delta_dist, (double[])
		{sqrt(1 + ((ray_dir[1] * ray_dir[1]) / (ray_dir[0] * ray_dir[0]))),
		sqrt(1 + ((ray_dir[0] * ray_dir[0]) / (ray_dir[1] * ray_dir[1]))), 0});
	ft_vec3_init(map_pos, (double[])
		{(int)ray_pos[0], (int)ray_pos[1], 0});
	ft_vec3_copy(data->actual_ray_dir, ray_dir);
	ft_vec3_copy(data->actual_ray_pos, ray_pos);
	init_step_and_side_dist(data, data->actual_step, data->actual_side_dist);
	while (1 == 1)
	{
		if (side_dist[0] < side_dist[1])
		{
			side_dist[0] += data->actual_delta_dist[0];
			map_pos[0] += data->actual_step[0];
			side = 0;
		}
		else
		{
			side_dist[1] += data->actual_delta_dist[1];
			map_pos[1] += data->actual_step[1];
			side = 1;
		}
		if (data->map[(int)map_pos[0]][(int)map_pos[1]] > 0)
		{
			// // printf("Collisison detected. - {%f - %f}\n", map_pos[0], map_pos[1]);
			break ;
		}
	}
	ret->side = side;
	ft_vec3_copy(ret->collision_pos, map_pos);

	if (side == 0)
		ret->corrected_dist = fabs((map_pos[0] - ray_pos[0] + (1 - data->actual_step[0]) / 2) / ray_dir[0]);
	else
		ret->corrected_dist = fabs((map_pos[1] - ray_pos[1] + (1 - data->actual_step[1]) / 2) / ray_dir[1]);
}

static void	draw_col(t_data *data, t_hit_info *hit, int x)
{
	int	height;
	int	start;
	int	end;
	int	y;

	height = (int)fabs(((double)data->h / hit->corrected_dist));
	start = (int)(-1 * height / 2 + data->h / 2);
	end = (int)(height / 2 + data->h / 2);

	if (start < 0)
		start = 0;
	if (end >= data->h)
		end = data->h - 1;
	y = 0;
	while (y < WIN_SIZE)
	{
		if (y < start)
			put_pixel_to_image(data, 0xAAAAAA, x, y);
		else if (y >= start && y <= end)
			put_pixel_to_image(data, 0xFFFFFF, x, y);
		else
			put_pixel_to_image(data, 0xAAAAAA, x, y);
		y++;
	}
	printf ("Start : %d and end : %d\n", start, end);
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
		get_ray(data, ray_pos, ray_dir, x);
		get_hit(data, ray_pos, ray_dir, &hit);
		draw_col(data, &hit, x);
		printf("wall touched distance : %f\n", hit.corrected_dist);
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
		render(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (1);
}
