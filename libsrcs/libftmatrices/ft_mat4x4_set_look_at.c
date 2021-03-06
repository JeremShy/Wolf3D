/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_set_look_at.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:01 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:03 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_set_look_at(t_mat4x4 matrice, const t_vec3 eye, const
	t_vec3 target, const t_vec3 up)
{
	t_vec3	xaxis;
	t_vec3	yaxis;
	t_vec3	zaxis;

	ft_vec3_sub(zaxis, eye, target);
	ft_vec3_normalize(zaxis);
	ft_vec3_cross(xaxis, up, zaxis);
	ft_vec3_normalize(xaxis);
	ft_vec3_cross(yaxis, zaxis, xaxis);
	matrice[0][0] = xaxis[0];
	matrice[0][1] = yaxis[0];
	matrice[0][2] = zaxis[0];
	matrice[0][3] = 0;
	matrice[1][0] = xaxis[1];
	matrice[1][1] = yaxis[1];
	matrice[1][2] = zaxis[1];
	matrice[1][3] = 0;
	matrice[2][0] = xaxis[2];
	matrice[2][1] = yaxis[2];
	matrice[2][2] = zaxis[2];
	matrice[2][3] = 0;
	matrice[3][0] = -1 * ft_vec3_dot(xaxis, eye);
	matrice[3][1] = -1 * ft_vec3_dot(yaxis, eye);
	matrice[3][2] = -1 * ft_vec3_dot(zaxis, eye);
	matrice[3][3] = 1;
}

void	ft_mat4x4_set_look_at_from_double_array(t_mat4x4 matrice,
	const double eye[3], const double target[3], const double up[3])
{
	t_vec3	vec_eye;
	t_vec3	vec_target;
	t_vec3	vec_up;

	ft_vec3_init(vec_eye, eye);
	ft_vec3_init(vec_target, target);
	ft_vec3_init(vec_up, up);
	ft_mat4x4_set_look_at(matrice, vec_eye, vec_target, vec_up);
}
