#include <wolf3d.h>

void rotate(t_data *data)
{
	float speed;

	if (data->rotating_left || data->rotating_right)
	{
		speed = (data->rotating_left ? 1 : -1) * ROTATE_SPEED;
		printf("ROTATING OF %f\n", speed);

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

int slide(t_data *data, t_vec3 movement)
{
	t_vec3			next_x;
	t_vec3			next_y;
	int8_t			tile_x;
	int8_t			tile_y;

	ft_vec3_init(next_x, (double[]){data->cam_pos[0] + movement[0], data->cam_pos[1], 0});
	ft_vec3_init(next_y, (double[]){data->cam_pos[0], data->cam_pos[1] + movement[1], 0});
	tile_x = data->map[(int)next_x[0]][(int)next_x[1]];
	tile_y = data->map[(int)next_y[0]][(int)next_y[1]];
	if (tile_x == 0 && tile_y != 0)
		ft_vec3_copy(data->cam_pos, next_x);
	else if (tile_y == 0 && tile_x != 0)
		ft_vec3_copy(data->cam_pos, next_y);
	else
		return (0);
	printf("ret 1\n");
	return (1);
}

// The player has to move depending of his direction
/*
	if direction is {-1, 0} and the player is going front
	 The player has to move of {-MOVEMENT_SPEED, 0}

	if (direction is {-1, 0}) and the player is going going_left
		the player has to move of {0, -MOVEMENT_SPEED}
*/

void	refresh_player(t_data *data)
{
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
		movement[0] = -1 * MOVEMENT_SPEED * data->cam_dir[1];
		movement[1] = MOVEMENT_SPEED * data->cam_dir[0];
	}
	else if (data->going_right)
	{
		movement[0] =  MOVEMENT_SPEED * data->cam_dir[1];
		movement[1] =  -1 * MOVEMENT_SPEED * data->cam_dir[0];
	}
	ft_vec3_add(next_pos, data->cam_pos, movement);
	next_tile = data->map[(int)next_pos[0]][(int)next_pos[1]];

	if (next_tile != 0) // Collision
	{
		if (!slide(data, movement))
			return ;
	}
	else
		ft_vec3_copy(data->cam_pos, next_pos);
	rotate(data);
	printf("player pos : \n");
	ft_vec3_print(data->cam_pos);
}
