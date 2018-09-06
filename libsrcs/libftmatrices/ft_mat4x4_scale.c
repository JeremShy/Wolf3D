/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_scale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:20:58 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:20:59 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_scale(t_mat4x4 matrice, const t_vec3 scale)
{
	t_mat4x4	scale_matrix;

	ft_mat4x4_set_scale(scale_matrix, scale);
	ft_mat4x4_mult(matrice, matrice, scale_matrix);
}
