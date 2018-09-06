/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_set_projection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:03 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:04 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_set_projection(t_mat4x4 m, const double array[4])
{
	double	fov;
	double	ratio;
	double	near;
	double	far;
	double	tan_half_fov;

	fov = array[0];
	ratio = array[1];
	near = array[2];
	far = array[3];
	ft_mat4x4_set_zero(m);
	tan_half_fov = tan(fov / 2);
	m[0][0] = 1 / (ratio * tan_half_fov);
	m[1][1] = 1 / tan_half_fov;
	m[2][2] = (-1 * (far + near)) / (far - near);
	m[3][2] = -1;
	m[2][3] = (-1 * (2 * far * near) / (far - near));
}
