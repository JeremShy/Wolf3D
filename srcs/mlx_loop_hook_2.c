/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:56:32 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:56:33 by jcamhi           ###   ########.fr       */
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
