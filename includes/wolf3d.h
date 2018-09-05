#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <mlx.h>
# include <ft_printf.h>
# include <libftmatrices.h>

# include <pthread.h>

# define WIN_SIZE 512
# define MOVEMENT_SPEED .1f
# define ROTATE_SPEED .05f

# define TEXTURE_NBR 5

# define WOOD_TEXTURE 0
# define STONE_TEXTURE 1
# define RDASH_TEXTURE 2
# define TWILIGHT_TEXTURE 3
# define PASSAGE_SECRET_TEXTURE 4

typedef enum e_orientation {
	NORTH,
	SOUTH,
	WEST,
	EAST
}						t_orientation;

typedef struct s_map_square
{
	int			num;
	int8_t	does_collide;
}				t_map_square;

typedef struct	s_img{
	void		*img;
	char		*addr;
	int			size_line;
	int			endian;
	int			bpp;
}								t_img;

typedef struct	s_draw_info
{
	int	y;
	int	real_start;
	int	real_end;
}								t_draw_info;

typedef struct	s_data {
	void		*mlx;
	void		*win;
	t_img		img;
	
	t_img		textures[TEXTURE_NBR];

	int		textures_size[TEXTURE_NBR][2];

	const char	*av;

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

	t_img		minimap;
	void		*minimap_save;
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
void	free_dtab(t_map_square **dtab, int size);

int		get_color_code(int r, int v, int b);
void	put_pixel_to_image(t_img *img, int color, int x, int y);
void	put_pixel_to_image_transparency(t_img *img, int64_t color, int x, int y);
void	clear_image(t_img *img, size_t h);
void	fill_image(t_img *img, size_t w, size_t h, int color);

int		loop_hook(void *data_void);
int		key_release_hook(int keycode, void *data_void);
int		key_press_hook(int keycode, void *data_void);
int		red_cross_hook(void *data);

int8_t	parse(t_data *data, const char *file);

void	refresh_player(t_data *data);

void get_first_x(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *first_x);
void get_first_y(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *first_y);

void	draw_col(t_data *data, t_hit_info *hit, int x);
void	darken(t_data *data, double ratio, t_vec3 from, t_vec3 to);

void	draw_minimap(t_data *data);

void	get_ray(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, int x);
void	get_hit(t_data *data, t_vec3 ray_pos, t_vec3 ray_dir, t_hit_info *ret);
void	render(t_data *data);
#endif
