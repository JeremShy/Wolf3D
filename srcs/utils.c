#include <wolf3d.h>

int		handle_error_void(void *variable, void *error_value, char *msg)
{
	if (variable == error_value)
	{
		ft_printf("%s\n", msg);
		return (1);
	}
	return (0);
}

void	free_dtab(int8_t **dtab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(dtab[i]);
		i++;
	}
	free(dtab);
}
