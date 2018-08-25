#include <wolf3d.h>

void get_first_x(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *first_x)
{
	int	map_pos[2];
	t_vec3 first_inter;
	double yb;
	double ab;
	double yd;
	double bd;
	t_vec3 delta_x;
	t_vec3 actual_pos;

	first_x->error = 1;

	map_pos[0] = (int)ray_pos[0];
	map_pos[1] = (int)ray_pos[1];

	if (ray_dir[1] == 0)
	{
		// printf("X error 19\n");
		return ;
	}

	// printf("x ray_pos : %f - %f\n", ray_pos[0], ray_pos[1]);
	// printf("x ray_dir : %f - %f\n", ray_dir[0], ray_dir[1]);

	yb = ray_dir[1] > 0. ? (int)(ray_pos[1]) + 1 : (int)ray_pos[1];

	ab = (yb - ray_pos[1]) / ray_dir[1];
	ft_vec3_init(first_inter, (double[]){
		ab * ray_dir[0] + ray_pos[0],
		ab * ray_dir[1] + ray_pos[1],
		0.
	});
	yd = ray_dir[1] > 0. ? (int)first_inter[1] + 1 : (int)first_inter[1] - 1;
	bd = (yd - first_inter[1]) / ray_dir[1];
	ft_vec3_init(delta_x, (double[]){
		ray_dir[0] * bd,
		(yd - first_inter[1]),
		0});
	ft_vec3_copy(actual_pos, first_inter);
	while (1)
	{
		// printf("Testing intersection : (%f,%f)\n", actual_pos[0], actual_pos[1]);
		if (actual_pos[0] < 0. || actual_pos[0] >= (double)data->size_y || actual_pos[1] < 0. || actual_pos[1] >= (double)data->size_x)
		{
			return ;
		}
		if (	data->map[(int)actual_pos[0]][(int)actual_pos[1]    ] != 0
			||	(actual_pos[1] - 1 >= 0 && data->map[(int)actual_pos[0]][(int)actual_pos[1] - 1] != 0))
		{
			ft_vec3_copy(first_x->collision_pos, actual_pos);
			first_x->side = 1;
			first_x->error = 0;
			if (actual_pos[1] - 1 >= 0 && data->map[(int)actual_pos[0]][(int)actual_pos[1] - 1] != 0)
			{
				first_x->orientation = NORTH;
				ft_memcpy(first_x->collided_wall, (int[2]){(int)actual_pos[0], (int)actual_pos[1] - 1}, sizeof(int) * 2);
			}
			else
			{
				first_x->orientation = SOUTH;
				ft_memcpy(first_x->collided_wall, (int[2]){(int)actual_pos[0], (int)actual_pos[1]}, sizeof(int) * 2);
			}
			return ;
		}
		ft_vec3_add(actual_pos, actual_pos, delta_x);
	}
}
