#include <wolf3d.h>

static void	get_first_inter(t_vec3 first_inter, t_vec3 ray_pos, t_vec3 ray_dir)
{
	double xb;
	double ab;

	xb = ray_dir[0] > 0 ? (int)(ray_pos[0]) + 1 : (int)ray_pos[0];
	ab = (xb - ray_pos[0]) / ray_dir[0];
	ft_vec3_init(first_inter, (double[]){ab * ray_dir[0] + ray_pos[0],
		ab * ray_dir[1] + ray_pos[1], 0.});
}

static void	get_delta_y(t_vec3 delta_y, t_vec3 ray_dir, t_vec3 first_inter)
{
	double xc;
	double bc;

	xc = ray_dir[0] > 0 ? (int)(first_inter[0]) + 1 :
		(int)(first_inter[0]) - 1;
	bc = (xc - first_inter[0]) / ray_dir[0];
	ft_vec3_init(delta_y, (double[]){xc - first_inter[0], ray_dir[1] * bc, 0});
}

static void	east_west_collision(t_vec3 ap, t_hit_info *first_y, t_data *d)
{
	if (ap[0] - 1 >= 0 && d->map[(int)ap[0] - 1][(int)ap[1]].num != 0)
	{
		first_y->orientation = WEST;
		ft_memcpy(first_y->collided_wall,
			(int[2]){(int)ap[0] - 1, (int)ap[1]}, sizeof(int) * 2);
	}
	else
	{
		first_y->orientation = EAST;
		ft_memcpy(first_y->collided_wall,
			(int[2]){(int)ap[0], (int)ap[1]}, sizeof(int) * 2);
	}
}

static void	boucle(t_vec3 first_inter, t_vec3 delta_y, t_data *d,
	t_hit_info *first_y)
{
	t_vec3 ap;

	ft_vec3_copy(ap, first_inter);
	while (1)
	{
		if (ap[0] < 0. || ap[0] >= (double)d->size_y
			|| ap[1] < 0. || ap[1] >= (double)d->size_x)
			return ;
		if ((ap[0] - 1 >= 0 && d->map[(int)ap[0] - 1][(int)ap[1]].num != 0)
			|| d->map[(int)ap[0]][(int)ap[1]].num != 0)
		{
			ft_vec3_copy(first_y->collision_pos, ap);
			first_y->side = 0;
			first_y->error = 0;
			east_west_collision(ap, first_y, d);
			return ;
		}
		ft_vec3_add(ap, ap, delta_y);
	}
}

void		get_first_y(t_data *data, t_vec3 ray_pos,
	t_vec3 ray_dir, t_hit_info *first_y)
{
	t_vec3 first_inter;
	t_vec3 delta_y;

	first_y->error = 1;
	if (ray_dir[0] == 0)
		return ;
	get_first_inter(first_inter, ray_pos, ray_dir);
	get_delta_y(delta_y, ray_dir, first_inter);
	boucle(first_inter, delta_y, data, first_y);
}
