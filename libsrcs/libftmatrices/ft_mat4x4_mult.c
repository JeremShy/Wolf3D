/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_mult.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:20:47 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:23:46 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

static void		compound_mult(t_mat4x4 ret, const t_mat4x4 m2)
{
	t_mat4x4	tmp;

	ft_mat4x4_copy(tmp, ret);
	ft_mat4x4_mult(ret, tmp, m2);
}

static double	get_res_at(const t_mat4x4 a, const t_mat4x4 b,
	int8_t i, int8_t j)
{
	int8_t	k;
	double	sum;

	k = 0;
	sum = 0;
	while (k < 4)
	{
		sum += a[i][k] * b[k][j];
		k++;
	}
	return (sum);
}

void			ft_mat4x4_mult(t_mat4x4 ret,
	const t_mat4x4 m1, const t_mat4x4 m2)
{
	int8_t	i;
	int8_t	j;

	if (ret == m1)
		return (compound_mult(ret, m2));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret[i][j] = get_res_at(m1, m2, i, j);
			j++;
		}
		i++;
	}
}
