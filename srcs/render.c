#include <wolf3d.h>

void	*render_0(void *vdata)
{
	t_data		*data;
	int			x;
	t_vec3		ray_pos;
	t_vec3		ray_dir;
	t_hit_info	hit;

	data = (t_data*)vdata;
	x = 0;
	while (x < data->w / 4)
	{
		get_ray(data, ray_pos, ray_dir, x);
		get_hit(data, ray_pos, ray_dir, &hit);
		draw_col(data, &hit, x);
		x++;
	}
	pthread_exit(NULL);
}

void	*render_1(void *vdata)
{
	t_data		*data;
	int			x;
	t_vec3		ray_pos;
	t_vec3		ray_dir;
	t_hit_info	hit;

	data = (t_data*)vdata;
	x = data->w / 4;
	while (x < 2 * data->w / 4)
	{
		get_ray(data, ray_pos, ray_dir, x);
		get_hit(data, ray_pos, ray_dir, &hit);
		draw_col(data, &hit, x);
		x++;
	}
	pthread_exit(NULL);
}

void	*render_2(void *vdata)
{
	t_data		*data;
	int			x;
	t_vec3		ray_pos;
	t_vec3		ray_dir;
	t_hit_info	hit;

	data = (t_data*)vdata;
	x = 2 * data->w / 4;
	while (x < 3 * data->w / 4)
	{
		get_ray(data, ray_pos, ray_dir, x);
		get_hit(data, ray_pos, ray_dir, &hit);
		draw_col(data, &hit, x);
		x++;
	}
	pthread_exit(NULL);
}

void	*render_3(void *vdata)
{
	t_data		*data;
	int			x;
	t_vec3		ray_pos;
	t_vec3		ray_dir;
	t_hit_info	hit;

	data = (t_data*)vdata;
	x = 3 * data->w / 4;
	while (x < data->w)
	{
		get_ray(data, ray_pos, ray_dir, x);
		get_hit(data, ray_pos, ray_dir, &hit);
		draw_col(data, &hit, x);
		x++;
	}
	pthread_exit(NULL);
}

void	render(t_data *data)
{
	pthread_t threads[4];

	pthread_create(threads + 0, NULL, render_0, (void*)data);
	pthread_create(threads + 1, NULL, render_1, (void*)data);
	pthread_create(threads + 2, NULL, render_2, (void*)data);
	pthread_create(threads + 3, NULL, render_3, (void*)data);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);
}
