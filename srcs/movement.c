#include <wolf3d.h>

// The player has to move depending of his direction
/*
	if direction is {-1, 0} and the player is going front
	 The player has to move of {-MOVEMENT_SPEED, 0}

	if (direction is {-1, 0}) and the player is going going_left
		the player has to move of {0, -MOVEMENT_SPEED}
*/

void rotate(t_data *data)
{
	if (data->rotating)
	{
		printf("ROTATING OF %f\n", data->actual_rotation_speed);

		ft_vec3_init(data->cam_dir, (double[]){
			data->cam_dir[0] * cos(data->actual_rotation_speed) - data->cam_dir[1] * sin(data->actual_rotation_speed),
			data->cam_dir[0] * sin(data->actual_rotation_speed) + data->cam_dir[1] * cos(data->actual_rotation_speed),
			0
		});

		ft_vec3_init(data->cam_plane, (double[]){
			data->cam_plane[0] * cos(data->actual_rotation_speed) - data->cam_plane[1] * sin(data->actual_rotation_speed),
			data->cam_plane[0] * sin(data->actual_rotation_speed) + data->cam_plane[1] * cos(data->actual_rotation_speed),
			0
		});

	}
}

void	refresh_player(t_data *data)
{
	//TODO : Move
	t_vec3		movement;
	t_vec3		next_pos;
	int8_t		next_tile;

	ft_vec3_init(movement, (double[3]){0, 0, 0});
	if (data->going_front)
	{
		movement[0] = MOVEMENT_SPEED * data->cam_dir[0];
		movement[1] = MOVEMENT_SPEED * data->cam_dir[1];
	}
	else if (data->going_back)
	{
		movement[0] =  -1 * MOVEMENT_SPEED * data->cam_dir[0];
		movement[1] =  -1 * MOVEMENT_SPEED * data->cam_dir[1];
	}
	if (data->going_left)
	{
		movement[0] = MOVEMENT_SPEED * data->cam_dir[1];
		movement[1] = MOVEMENT_SPEED * data->cam_dir[0];
	}
	else if (data->going_right)
	{
		movement[0] =  -1 * MOVEMENT_SPEED * data->cam_dir[1];
		movement[1] =  -1 * MOVEMENT_SPEED * data->cam_dir[0];
	}
	ft_vec3_add(next_pos, data->cam_pos, movement);
	next_tile = data->map[(int)next_pos[1]][(int)next_pos[0]];

	if (next_tile != 0) // Collision
		return ;
	ft_vec3_copy(data->cam_pos, next_pos);
	rotate(data);
	sync_map_squares(data);
	printf("player pos : \n");
	ft_vec3_print(data->cam_pos);
}
