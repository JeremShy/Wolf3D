/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:52:12 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:52:13 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <fcntl.h>

static int8_t	allocate_map(t_data *data)
{
	int	i;

	if ((data->map = malloc(sizeof(t_map_square*) * data->size_y)) == NULL)
		return (0);
	i = 0;
	while (i < data->size_y)
	{
		data->map[i] = malloc(sizeof(t_map_square) * data->size_x);
		if (data->map[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}

static int8_t	parse_line(t_data *data, int line_number, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == data->size_x)
			return (0);
		else if (ft_isdigit(str[i]))
		{
			data->map[line_number][i].num = str[i] - '0';
			data->map[line_number][i].does_collide =
				(str[i] - '0' == 5 || str[i] - '0' == 0 ? 0 : 1);
		}
		else
			return (0);
		i++;
	}
	if (i != data->size_x)
		return (0);
	return (1);
}

int8_t			parse_2(t_data *data, char *str, int fd)
{
	int	i;

	if (!allocate_map(data))
	{
		ft_printf("%s: couldn't allocate map\n", data->av);
		return (return_close_free(str, fd, 0));
	}
	if (!parse_line(data, 0, str))
		return (return_close_free(str, fd, 0));
	free(str);
	i = 1;
	while (get_next_line(fd, &str) > 0)
	{
		if (parse_line(data, i, str) == 0)
			return (return_close_free(str, fd, 0));
		i++;
		free(str);
	}
	close(fd);
	return (1);
}

int8_t			parse(t_data *data, const char *file)
{
	int		fd;
	char	*str;
	int		r;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Can't open file `", 2);
		ft_putstr_fd((char*)file, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if ((r = get_size_y(file)) == 0)
		return (0);
	data->size_y = r;
	r = get_next_line(fd, &str);
	if (r == 0 || r == -1)
		return (return_close_free(NULL, fd, 0));
	if (!get_size_x(data, str))
	{
		ft_printf("%s: invalid first line\n", data->av);
		return (return_close_free(str, fd, 0));
	}
	return (parse_2(data, str, fd));
}
