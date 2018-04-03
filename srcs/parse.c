#include <wolf3d.h>
#include <fcntl.h>

static int8_t	validate_line(char *str, int size_x)
{
	int	i;

	i = 0;
	while ((size_x < 0 || i < size_x) && str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int8_t	get_size_x(t_data *data, char *str)
{
	int	i;
	int	x;

	if	(!validate_line(str, -1))
		return (0);
	i = 0;
	x = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			x++;
		i++;
	}
	printf("X size : %d\n", x);
	data->size_x = x;
	return (1);
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
		printf("str : %s\n", str);
		free(str);
		i++;
	}
	ft_printf("max y : %d\n", i);
	close(fd);
	return (i);
}

static int8_t	allocate_map(t_data *data)
{
	int	i;

	if ((data->map = malloc(sizeof(char*) * (data->size_y + 1))) == NULL)
		return (0);
	i = 0;
	while (i < data->size_y)
	{
		data->map[i] = malloc(sizeof(char) * (data->size_x + 1));
		if (data->map[i] == NULL)
			return (0);
		i++;
	}
	data->map[i] = NULL;
	return (1);
}

int8_t			parse(t_data *data, const char *file)
{
	int		fd;
	char	*str;
	int		r;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("Can't open file `%s'\n", file);
		return (0);
	}
	if ((r = get_size_y(file)) == 0)
		return (0);
	data->size_y = r;
	r = get_next_line(fd, &str);
	if (r == 0 || r == -1)
	{
		if (r == 0)
			free(str);
		close(fd);
		return (0);
	}
	if (!get_size_x(data, str))
	{
		printf("%s: invalid first line\n", data->av);
		free(str);
		close(fd);
		return (0);
	}
	if (!allocate_map(data))
	{
		printf("%s: couldn't allocate map\n", data->av);
		free(str);
		close(fd);
		return (0);		
	}
	close(fd);
	return (1);
}
