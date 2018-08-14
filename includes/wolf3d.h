#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <mlx.h>
# include <ft_printf.h>
# include <libftmatrices.h>

# define WIN_SIZE 512
# define MOVEMENT_SPEED .1f

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	const char	*av;

	int			size_line;
	int			endian;
	int			bpp;

	double		global_rotation_speed;

	int8_t		**map;
	int			size_x;
	int			size_y;

	t_vec3		cam_pos;	// {0 <=> size_x, 0 <=> size_y}
	t_vec3		cam_square; // (It is the position of the camera as a square in the map, instead of as a float position)
	t_vec3		cam_dir;	// -1 <=> 1  - Vers ou on est tourne
	t_vec3		cam_plane;	// Plan de la camera (Perpendiculaaire a la direction de la camera). Le FOV est un ration entre la taille du vecteur de dirction et celui du plan de la camera

	double		w;			// En pixel
	double		h;			// En pixel

	int8_t		going_front;
	int8_t		going_back;
	int8_t		going_left;
	int8_t		going_right;

	int8_t		rotating;

	double		actual_rotation_speed;

	int8_t		must_refresh;

	t_vec3		actual_ray_dir;
	t_vec3		actual_ray_pos;
	t_vec3		actual_delta_dist;
	t_vec3		actual_step;
	t_vec3		actual_side_dist;
}				t_data;

typedef struct	s_hit_info {
		int8_t	side;
		t_vec3	collision_pos;
		double	corrected_dist;
}				t_hit_info;

int		init_the_mlx(t_data *data);
void	free_mlx_and_exit(t_data *data);

int		handle_error_void(void *variable, void *error_value, char *msg);
void	free_dtab(int8_t **dtab, int size);
void	sync_map_squares(t_data *data);

int		get_color_code(int r, int v, int b);
void	put_pixel_to_image(t_data *data, int color, int x, int y);
void	clear_image(t_data *data);
void	fill_image(t_data *data, int color);

int		loop_hook(void *data_void);
int		key_release_hook(int keycode, void *data_void);
int		key_press_hook(int keycode, void *data_void);
int		red_cross_hook(void *data);

int8_t	parse(t_data *data, const char *file);

void	print_map(t_data *data);

void	refresh_player(t_data *data);


#endif
