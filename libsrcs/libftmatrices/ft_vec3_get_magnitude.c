/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_get_magnitude.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:21 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:22 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

double	ft_vec3_get_magnitude(const t_vec3 vector)
{
	return (sqrt(vector[0] * vector[0] + vector[1] *
		vector[1] + vector[2] * vector[2]));
}
