#include "libft.h"

char	*ft_strnchr(const char *s, int c, unsigned int n)
{
    unsigned int i;

    i = 0;
    if (!s || !n)
    {
		return (NULL);
	}
	while (s[i] && i < n)
	{
		if ((unsigned char)c == s[i])
			return ((char *)&s[i]);
		i++;
	}
	if (i < n && (unsigned char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}