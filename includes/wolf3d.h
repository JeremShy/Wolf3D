#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <mlx.h>
# include <ft_printf.h>
# include <libftmatrices.h>

# define WIN_SIZE 840

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

	t_vec3		cam_pos;
	t_vec3		cam_dir;
	t_vec3		cam_plane;

	double		w;
	double		h;

	int8_t		going_front;
	int8_t		going_back;
	int8_t		going_left;
	int8_t		going_right;

	int8_t		rotating;

	double		actual_rotation_speed;

	int8_t		must_refresh;
}				t_data;

int		init_the_mlx(t_data *data);
void	free_mlx_and_exit(t_data *data);

int		handle_error_void(void *variable, void *error_value, char *msg);

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

#endif
