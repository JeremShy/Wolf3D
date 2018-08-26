#include <wolf3d.h>
#include <fcntl.h>

static int8_t	validate_line(char *str, int size_x)
{
	int	i;

	i = 0;
	while ((size_x < 0 || i < size_x) && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int8_t	get_size_x(t_data *data, char *str)
{
	int	i;

	if	(!validate_line(str, -1))
		return (0);
	i = 0;
	while (str[i])
		i++;
	data->size_x = i;
	return (1);
}

static int8_t	return_close_free(char *str, int fd, int ret)
{
	if (str)
		free(str);
	close(fd);
	return (ret);
}

static int		get_size_y(const char *file)
{
	int		i;
	int		fd;
	char	*str;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("Can't open file `%s'\n", file);
		return (0);
	}
	while (get_next_line(fd, &str) > 0)
	{
		free(str);
		i++;
	}
	close(fd);
	return (i);
}

static int8_t	allocate_map(t_data *data)
{
	int	i;

	if ((data->map = malloc(sizeof(char*) * data->size_y)) == NULL)
		return (0);
	i = 0;
	while (i < data->size_y)
	{
		data->map[i] = malloc(sizeof(char) * data->size_x);
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
			data->map[line_number][i] = str[i] - '0';
		else
			return (0);
		i++;
	}
	if (i != data->size_x)
		return (0);
	return (1);
}

int8_t			parse(t_data *data, const char *file)
{
	int		fd;
	char	*str;
	int		r;
	int		i;

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
		return return_close_free(NULL, fd, 0);
	if (!get_size_x(data, str))
	{
		ft_printf("%s: invalid first line\n", data->av);
		return return_close_free(str, fd, 0);
	}
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
