/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3_normalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:21:24 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:21:25 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_vec3_normalize(t_vec3 vector)
{
	double	magnitude;

	magnitude = ft_vec3_get_magnitude(vector);
	vector[0] = vector[0] / magnitude;
	vector[1] = vector[1] / magnitude;
	vector[2] = vector[2] / magnitude;
}
