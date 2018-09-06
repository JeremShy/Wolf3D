/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_scale_from_double_array.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:20:59 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:00 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_scale_from_double_array(t_mat4x4 matrice,
	const double array[3])
{
	t_vec3	vector;

	ft_vec3_init(vector, array);
	ft_mat4x4_scale(matrice, vector);
}
