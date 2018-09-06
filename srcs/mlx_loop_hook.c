/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:52:07 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:52:09 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			get_ray(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, int x)
{
	double	col_pos;

	col_pos = 2. * x / (double)data->w - 1.;
	ft_vec3_copy(ray_pos, data->cam_pos);
	ft_vec3_init(ray_dir,
	(double[]){data->cam_dir[0] + data->cam_plane[0] * col_pos,
			data->cam_dir[1] + data->cam_plane[1] * col_pos, 0});
	ft_vec3_normalize(ray_dir);
}

static double	correct_distance(t_vec3 ray_pos, t_hit_info collision)
{
	return (sqrt((collision.collision_pos[0] - ray_pos[0])
		* (collision.collision_pos[0] - ray_pos[0]) +
		(collision.collision_pos[1]
		- ray_pos[1]) * (collision.collision_pos[1] - ray_pos[1])));
}

t_hit_info		*compute_ret(t_hit_info *first_x,
	t_hit_info *first_y, t_vec3 ray_pos)
{
	if (first_y->error != 1)
		first_y->corrected_dist = correct_distance(ray_pos, *first_y);
	if (first_x->error == 0 && first_y->error == 1)
		return (first_x);
	else if (first_x->error == 1 && first_y->error == 0)
		return (first_y);
	else
		return (first_x->corrected_dist <
			first_y->corrected_dist ? first_x : first_y);
}

void			get_hit(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir,
		t_hit_info *ret)
{
	t_hit_info	first_x;
	t_hit_info	first_y;
	t_vec3		ab;
	t_vec3		look_dir;

	ft_bzero(&first_x, sizeof(t_hit_info));
	get_first_x(data, ray_pos, ray_dir, &first_x);
	if (first_x.error != 1)
		first_x.corrected_dist = correct_distance(ray_pos, first_x);
	get_first_y(data, ray_pos, ray_dir, &first_y);
	if (first_x.error == 1 && first_y.error == 1)
	{
		ft_putstr_fd("Error : A ray hit no box, does the map have a hole ?\n",
			2);
		return (exit(3));
	}
	*ret = *compute_ret(&first_x, &first_y, ray_pos);
	ft_vec3_init(ab, (double[]){ret->collision_pos[0] - ray_pos[0],
		ret->collision_pos[1] - ray_pos[1], 0});
	ft_vec3_copy(look_dir, data->cam_dir);
	ft_vec3_normalize(look_dir);
	ret->corrected_dist = ft_vec3_dot(ab, look_dir);
}

static void		handle_pause(t_data *data)
{
	t_vec3	darken_from;
	t_vec3	darken_to;

	ft_vec3_init(darken_from, (double[]){0, 0, 0});
	ft_vec3_init(darken_to, (double[]){data->w, data->h, 0});
	darken(data, .2, darken_from, darken_to);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_string_put(data->mlx, data->win, data->w / 2,
		data->h / 4, 0xff0000, "PAUSED");
}

int				loop_hook(void *data_void)
{
	t_data	*data;

	data = (t_data*)data_void;
	if (data->must_refresh || data->going_back || data->going_front ||
		data->going_left || data->going_right || data->rotating_left ||
		data->rotating_right)
	{
		data->must_refresh = 0;
		if (data->paused == 1)
		{
			handle_pause(data);
			return (1);
		}
		clear_image(&data->img, data->h);
		refresh_player(data);
		render(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
		draw_minimap(data);
	}
	return (1);
}
