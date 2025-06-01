#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>

char	**ft_split(char *str, char charset);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strstr(const char *str, const char *to_find);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *s, int c);
size_t  ft_strlen(char *s);

#endif