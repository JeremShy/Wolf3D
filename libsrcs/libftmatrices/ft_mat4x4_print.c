/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat4x4_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 19:20:51 by jcamhi            #+#    #+#             */
/*   Updated: 2018/09/06 19:20:53 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftmatrices.h>

void	ft_mat4x4_print(const t_mat4x4 matrice)
{
	int	i;

	i = 0;
	printf("--------------------------------------------------------------\n");
	while (i < 4)
	{
		printf("|\t%-4f|\t%-4f|\t%-4f|\t%-4f|\n", matrice[i][0], matrice[i][1],
			matrice[i][2], matrice[i][3]);
		i++;
	}
	printf("--------------------------------------------------------------\n");
}
