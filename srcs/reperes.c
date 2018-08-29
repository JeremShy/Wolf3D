#include <wolf3d.h>

void	maths_to_screen(t_data *data, t_vec3 maths_pos, t_vec3 screen_pos)
{
	ft_vec3_init(screen_pos, (double[]){
		maths_pos[0],
		data->size_y - maths_pos[1],
		0
	});
}