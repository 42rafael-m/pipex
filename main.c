#include <string.h>
#include <stdio.h>
#include <stdlib.h>
# define ESC_CHARS "\\\'\"\?abfnrtv"

static int  ft_len(char *s)
{
    int r;
    int i;

    r = 0;
    i = 0;
    if (!s)
        return (-1);
    while (s[i])
    {
        if (s[i] == '\\' && strchr(ESC_CHARS, s[i + 1]))
            i++;
        r++;
        i++;
    }
    return (r);
}

char	*ft_esc_char(char *s)
{
    int len;
    char    *r;
    int i;
    int j;
    
    i = 0;
    j = 0;
    if (!s)
        return (NULL);
    len = ft_len(s);
    r = (char *)ft_calloc(len + 1, sizeof(char));
    if (!r)
        return (NULL);
    while (s[i])
    {
        if (s[i] == '\\' && strchr(ESC_CHARS, s[i + 1]))
            i += 2;
        r[j] = s[i];
        i++;
        j++;
    }
    return (r);
}

int main()
{
    char *s = "123\\a123\\1\\";
    char *r = ft_esc_char(s);
    write(1, "escaped = ", 10);
    write(1, r, strlen(r));
    write(1, "\n", 1);
    write(1, "not escaped = ", 14);
    write(1, s, strlen(s));
    write(1, "\n", 1);
}