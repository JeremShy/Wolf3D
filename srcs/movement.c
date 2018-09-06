/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:52:10 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:52:11 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		rotate(t_data *data)
{
	float speed;

	if (data->rotating_left || data->rotating_right)
	{
		speed = (data->rotating_left ? 1 : -1) * ROTATE_SPEED;
		ft_vec3_init(data->cam_dir, (double[]){
			data->cam_dir[0] * cos(speed) - data->cam_dir[1] * sin(speed),
			data->cam_dir[0] * sin(speed) + data->cam_dir[1] * cos(speed),
			0
		});
		ft_vec3_init(data->cam_plane, (double[]){
			data->cam_plane[0] * cos(speed) - data->cam_plane[1] * sin(speed),
			data->cam_plane[0] * sin(speed) + data->cam_plane[1] * cos(speed),
			0
		});
	}
}

int			slide(t_data *data, t_vec3 movement)
{
	t_vec3					next_x;
	t_vec3					next_y;
	t_map_square			tile_x;
	t_map_square			tile_y;

	ft_vec3_init(next_x, (double[]){data->cam_pos[0] + movement[0],
		data->cam_pos[1], 0});
	ft_vec3_init(next_y, (double[]){data->cam_pos[0],
		data->cam_pos[1] + movement[1], 0});
	tile_x = data->map[(int)next_x[0]][(int)next_x[1]];
	tile_y = data->map[(int)next_y[0]][(int)next_y[1]];
	if (tile_x.does_collide == 0 && tile_y.does_collide != 0)
		ft_vec3_copy(data->cam_pos, next_x);
	else if (tile_y.does_collide == 0 && tile_x.does_collide != 0)
		ft_vec3_copy(data->cam_pos, next_y);
	else
		return (0);
	return (1);
}

int			check_collision(t_data *data, t_vec3 movement)
{
	t_map_square		next_tile;
	t_vec3				next_pos;
	t_map_square		next_tile_x;
	t_map_square		next_tile_y;

	ft_vec3_add(next_pos, data->cam_pos, movement);
	if (next_pos[0] != data->cam_pos[0] && next_pos[1] != data->cam_pos[1])
	{
		next_tile_x = data->map[(int)next_pos[0]][(int)data->cam_pos[1]];
		next_tile_y = data->map[(int)data->cam_pos[0]][(int)next_pos[1]];
		if (next_tile_x.does_collide == 1 || next_tile_y.does_collide == 1)
			return (0);
	}
	next_tile = data->map[(int)next_pos[0]][(int)next_pos[1]];
	return (next_tile.does_collide == 0);
}

static void	calculate_movement(t_data *data, t_vec3 movement)
{
	if (data->going_front)
	{
		movement[0] = MOVEMENT_SPEED * data->cam_dir[0];
		movement[1] = MOVEMENT_SPEED * data->cam_dir[1];
	}
	else if (data->going_back)
	{
		movement[0] = -1 * MOVEMENT_SPEED * data->cam_dir[0];
		movement[1] = -1 * MOVEMENT_SPEED * data->cam_dir[1];
	}
	if (data->going_left)
	{
		movement[0] = -1 * MOVEMENT_SPEED * data->cam_dir[1];
		movement[1] = MOVEMENT_SPEED * data->cam_dir[0];
	}
	else if (data->going_right)
	{
		movement[0] = MOVEMENT_SPEED * data->cam_dir[1];
		movement[1] = -1 * MOVEMENT_SPEED * data->cam_dir[0];
	}
}

void		refresh_player(t_data *data)
{
	t_vec3				movement;

	ft_vec3_init(movement, (double[3]){0, 0, 0});
	calculate_movement(data, movement);
	if (!check_collision(data, movement))
	{
		if (!slide(data, movement))
			return ;
	}
	else
		ft_vec3_add(data->cam_pos, data->cam_pos, movement);
	rotate(data);
}
