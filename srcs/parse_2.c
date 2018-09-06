/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:58:01 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 18:58:01 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int8_t	validate_line(char *str, int size_x)
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

int8_t	get_size_x(t_data *data, char *str)
{
	int	i;

	if (!validate_line(str, -1))
		return (0);
	i = 0;
	while (str[i])
		i++;
	data->size_x = i;
	return (1);
}

int8_t	return_close_free(char *str, int fd, int ret)
{
	if (str)
		free(str);
	close(fd);
	return (ret);
}

int		get_size_y(const char *file)
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
