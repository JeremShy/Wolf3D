#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <mlx.h>
# include <ft_printf.h>
# include <libftmatrices.h>

# define WIN_SIZE 512
# define MOVEMENT_SPEED .1f
# define ROTATE_SPEED .05f

# define TEXTURE_NBR 4

# define WOOD_TEXTURE 0
# define STONE_TEXTURE 1
# define RDASH_TEXTURE 2
# define TWILIGHT_TEXTURE 3

typedef enum e_orientation {
	NORTH,
	SOUTH,
	WEST,
	EAST
}						t_orientation;

typedef struct s_map_square
{
	int			num;
}				t_map_square;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;

	void		*textures[TEXTURE_NBR];
	int		textures_size[TEXTURE_NBR][2];
	char		*textures_addr[TEXTURE_NBR];

	int			textures_bpp[TEXTURE_NBR];
	int			textures_line_size[TEXTURE_NBR];
	int			textures_endian[TEXTURE_NBR];
	const char	*av;

	int			size_line;
	int			endian;
	int			bpp;

	t_map_square	**map;
	int			size_x;
	int			size_y;

	t_vec3		cam_pos;	// {0 <=> size_x, 0 <=> size_y}
	t_vec3		cam_dir;	// -1 <=> 1  - Vers ou on est tourne
	t_vec3		cam_plane;	// Plan de la camera (Perpendiculaaire a la direction de la camera). Le FOV est un ration entre la taille du vecteur de dirction et celui du plan de la camera

	double		w;			// En pixel
	double		h;			// En pixel

	int8_t		going_front;
	int8_t		going_back;
	int8_t		going_left;
	int8_t		going_right;

	int8_t		rotating_left;
	int8_t		rotating_right;

	int			paused;

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
		int8_t	error;
		int			collided_wall[2];
		t_orientation	orientation;
}				t_hit_info;

int		init_the_mlx(t_data *data);
void	free_mlx_and_exit(t_data *data);

int		handle_error_void(void *variable, void *error_value, char *msg);
void	free_dtab(int8_t **dtab, int size);

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

void get_first_x(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *first_x);
void get_first_y(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *first_y);

void	draw_col(t_data *data, t_hit_info *hit, int x);
void	darken(t_data *data, double ratio, t_vec3 from, t_vec3 to);

void	draw_minimap(t_data *data);

#endif
