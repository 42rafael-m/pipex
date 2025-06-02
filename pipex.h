/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:00 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/02 19:03:03 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

char	**ft_split(char *str, char charset);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *str, const char *to_find);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *s, int c);
size_t  ft_strlen(char *s);

#endif
