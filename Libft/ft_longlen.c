/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:09:39 by rafael-m          #+#    #+#             */
/*   Updated: 2025/04/22 12:40:59 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Devuelve el número de dígitos de un long pasado como parámetro. */

size_t	ft_longlen(long n)
{
        size_t	lg;

        lg = 1;
	if (n < 0)
	{
		n = -n;
		lg++;
	}
	while (n > 9)
	{
		n = n / 10;
		lg++;
	}
	return (lg);
}
