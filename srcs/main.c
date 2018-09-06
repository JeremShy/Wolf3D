/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:51:56 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:51:57 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	load_texture(t_data *d, int nbr, char *file)
{
	d->textures[nbr].img = mlx_xpm_file_to_image(d->mlx, file,
		&d->textures_size[nbr][0], &d->textures_size[nbr][1]);
	d->textures[nbr].addr = mlx_get_data_addr(d->textures[nbr].img,
		&(d->textures[nbr].bpp), &(d->textures[nbr].size_line),
		&(d->textures[nbr].endian));
}

static void	load_textures(t_data *data)
{
	load_texture(data, WOOD_TEXTURE, "textures/wood.xpm");
	load_texture(data, STONE_TEXTURE, "textures/stone.xpm");
	load_texture(data, RDASH_TEXTURE, "textures/rdash.xpm");
	load_texture(data, TWILIGHT_TEXTURE, "textures/twilight.xpm");
	load_texture(data, PASSAGE_SECRET_TEXTURE, "textures/passage_secret.xpm");
}

static void	prepare_data_n_mlx(t_data *data)
{
	ft_vec3_init(data->cam_pos, (double[]){1.7, 9.1, 0});
	ft_vec3_init(data->cam_dir, (double[]){0, 1, 0});
	ft_vec3_init(data->cam_plane, (double[]){.5, 0, 0});
	data->must_refresh = 1;
	mlx_hook(data->win, 17, (1L << 17), red_cross_hook, data);
	mlx_hook(data->win, 3, (1L << 1), key_release_hook, data);
	mlx_hook(data->win, 2, (1L << 0), key_press_hook, data);
	mlx_loop_hook(data->mlx, &loop_hook, data);
}

int			main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_printf("%s: usage: %s map\n", av[0], av[0]);
		return (1);
	}
	ft_bzero(&data, sizeof(data));
	data.av = av[0];
	if (!parse(&data, av[1]))
	{
		ft_printf("%s: parse error\n", av[0]);
		return (2);
	}
	data.w = 512;
	data.h = 512;
	if (!init_the_mlx(&data))
		return (0);
	clear_image(data.img.img, data.h);
	mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	load_textures(&data);
	prepare_data_n_mlx(&data);
	mlx_loop(data.mlx);
	return (0);
}
