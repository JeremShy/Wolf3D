/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:20:54 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:20:55 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_rotate(t_mat4x4 matrice, double angle, const t_vec3 axis)
{
	t_mat4x4	rotation_matrix;

	ft_mat4x4_set_rotation(rotation_matrix, angle, axis);
	ft_mat4x4_mult(matrice, matrice, rotation_matrix);
}
