/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:07:55 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/02 18:11:49 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_ptr(char	**ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (*ptr)
	{
		free (*ptr);
		*ptr = NULL;
		i++;
	}
	free (ptr);
	ptr = NULL;
	return ;
}
