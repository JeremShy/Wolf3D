/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_translate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:10 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:11 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_translate(t_mat4x4 m, const t_vec3 v)
{
	t_mat4x4	translation_matrix;

	ft_mat4x4_set_translation(translation_matrix, v);
	ft_mat4x4_mult(m, m, translation_matrix);
}
