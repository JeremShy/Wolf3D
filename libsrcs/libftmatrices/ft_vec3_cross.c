/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_cross.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:15 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:15 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

static void	compound_cross(t_vec3 dst, const t_vec3 v2)
{
	t_vec3	tmp;

	ft_vec3_copy(tmp, dst);
	ft_vec3_cross(dst, tmp, v2);
}

void		ft_vec3_cross(t_vec3 dst, const t_vec3 v1, const t_vec3 v2)
{
	if (dst == v1)
		return (compound_cross(dst, v2));
	dst[0] = v1[1] * v2[2] - v1[2] * v2[1];
	dst[1] = v1[2] * v2[0] - v1[0] * v2[2];
	dst[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
