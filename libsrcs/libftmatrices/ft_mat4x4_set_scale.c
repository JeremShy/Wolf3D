/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_set_scale.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:05 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:06 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_set_scale(t_mat4x4 matrix, const t_vec3 scale)
{
	ft_mat4x4_set_identity(matrix);
	matrix[0][0] = scale[0];
	matrix[1][1] = scale[1];
	matrix[2][2] = scale[2];
}
