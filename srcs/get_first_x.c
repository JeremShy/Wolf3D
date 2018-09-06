/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:51:52 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:51:53 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	get_first_inter(t_vec3 first_inter, t_vec3 ray_dir, t_vec3 ray_pos)
{
	double yb;
	double ab;

	yb = ray_dir[1] > 0. ? (int)(ray_pos[1]) + 1 : (int)ray_pos[1];
	ab = (yb - ray_pos[1]) / ray_dir[1];
	ft_vec3_init(first_inter, (double[]){ab * ray_dir[0] + ray_pos[0],
		ab * ray_dir[1] + ray_pos[1], 0.});
}

static void	get_delta_x(t_vec3 delta_x, t_vec3 ray_dir, t_vec3 first_inter)
{
	double yd;
	double bd;

	yd = ray_dir[1] > 0. ? (int)first_inter[1] + 1 : (int)first_inter[1] - 1;
	bd = (yd - first_inter[1]) / ray_dir[1];
	ft_vec3_init(delta_x, (double[]){ray_dir[0] * bd,
		(yd - first_inter[1]), 0});
}

static void	north_south_collision(t_vec3 ap, t_data *d, t_hit_info *first_x)
{
	if (ap[1] - 1 >= 0 && d->map[(int)ap[0]][(int)ap[1] - 1].num != 0)
	{
		first_x->orientation = NORTH;
		ft_memcpy(first_x->collided_wall, (int[2]){(int)ap[0],
			(int)ap[1] - 1}, sizeof(int) * 2);
	}
	else
	{
		first_x->orientation = SOUTH;
		ft_memcpy(first_x->collided_wall, (int[2]){(int)ap[0],
			(int)ap[1]}, sizeof(int) * 2);
	}
}

static void	boucle(t_vec3 first_inter, t_data *d,
	t_hit_info *first_x, t_vec3 delta_x)
{
	t_vec3 ap;

	ft_vec3_copy(ap, first_inter);
	while (1)
	{
		if (ap[0] < 0. || ap[0] >= (double)d->size_y
			|| ap[1] < 0. || ap[1] >= (double)d->size_x)
			return ;
		if (d->map[(int)ap[0]][(int)ap[1]].num != 0 || (ap[1] - 1 >= 0 &&
				d->map[(int)ap[0]][(int)ap[1] - 1].num != 0))
		{
			ft_vec3_copy(first_x->collision_pos, ap);
			first_x->side = 1;
			first_x->error = 0;
			north_south_collision(ap, d, first_x);
			return ;
		}
		ft_vec3_add(ap, ap, delta_x);
	}
}

void		get_first_x(t_data *data, t_vec3 ray_pos,
	t_vec3 ray_dir, t_hit_info *first_x)
{
	t_vec3	first_inter;
	t_vec3	delta_x;

	if (ray_dir[1] == 0)
		return ;
	first_x->error = 1;
	get_first_inter(first_inter, ray_dir, ray_pos);
	get_delta_x(delta_x, ray_dir, first_inter);
	boucle(first_inter, data, first_x, delta_x);
}
