#include <wolf3d.h>

void get_first_y(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *first_y)
{
	int	map_pos[2];
	t_vec3 first_inter;
	double xb;
	double ab;
	double xc;
	double bc;
	t_vec3 delta_y;
	t_vec3 actual_pos;

	map_pos[0] = (int)ray_pos[0];
	map_pos[1] = (int)ray_pos[1];
	first_y->error = 1;

	if (ray_dir[0] == 0)
	{
		// printf("Y error 1\n");
		return ;
	}

	// printf("y ray_pos : %f - %f\n", ray_pos[0], ray_pos[1]);
	// printf("y ray_dir : %f - %f\n", ray_dir[0], ray_dir[1]);

	xb = ray_dir[0] > 0 ? (int)(ray_pos[0]) + 1 : (int)ray_pos[0];

	ab = (xb - ray_pos[0]) / ray_dir[0];
	ft_vec3_init(first_inter, (double[]){
		ab * ray_dir[0] + ray_pos[0],
		ab * ray_dir[1] + ray_pos[1],
		0.
	});

	xc = ray_dir[0] > 0 ? (int)(first_inter[0]) +	 1 : (int)(first_inter[0]) - 1;
	bc = (xc - first_inter[0]) / ray_dir[0];

	ft_vec3_init(delta_y, (double[]){
		xc - first_inter[0],
		ray_dir[1] * bc,
		0
	});
	ft_vec3_copy(actual_pos, first_inter);
	while (1)
	{
		// printf("Testing intersection : (%f,%f)\n", actual_pos[0], actual_pos[1]);
		if (actual_pos[0] < 0. || actual_pos[0] >= (double)data->size_y || actual_pos[1] < 0. || actual_pos[1] >= (double)data->size_x)
		{
			// printf("Y error 2\n");;
			return ;
		}
		if (   (actual_pos[0] - 1 >= 0 && data->map[(int)actual_pos[0] - 1 ][(int)actual_pos[1]] != 0)
				|| data->map[(int)actual_pos[0]			][(int)actual_pos[1]] != 0)
		{
			ft_vec3_copy(first_y->collision_pos, actual_pos);
			first_y->side = 0;
			first_y->error = 0;
			if (actual_pos[0] - 1 >= 0 && data->map[(int)actual_pos[0] - 1][(int)actual_pos[1]] != 0)
			{
				first_y->orientation = WEST;
				ft_memcpy(first_y->collided_wall, (int[2]){(int)actual_pos[0] - 1, (int)actual_pos[1]}, sizeof(int) * 2);
			}
			else
			{
				first_y->orientation = EAST;
				ft_memcpy(first_y->collided_wall, (int[2]){(int)actual_pos[0], (int)actual_pos[1]}, sizeof(int) * 2);
			}
			return ;
		}
		ft_vec3_add(actual_pos, actual_pos, delta_y);

	}
}
