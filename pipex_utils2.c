#include "pipex.h"
#include "libft/libft.h"

char    **ft_argv(char *cmd)
{
    int block;
    char    **argv;
    int i;
    int j;
    int space;
    int start;

    i = 1;
    j = 1;
    block = 0;
    space = 0;
    start = ft_spacelen(cmd) + 1;
    if (!ft_strchr(cmd, 34) && !ft_strchr(cmd, 39) && !ft_strchr(cmd, 123))
        return (ft_split(cmd, ' '));
    while (cmd[i])
    {
        if (cmd[i] == 123 || cmd[i] == 34 || cmd[i] == 39)
            block = 1;
        if (cmd[i] == 125 || cmd[i] == 34 || cmd[i] == 39)
            block = 0;
        if (cmd[i] == 32 && !block)
            space++;
        i++;
    }
    argv = (char **)ft_calloc(space + 2, sizeof(char *));
    argv[0] = ft_substr(cmd, 0, ft_spacelen(cmd));
    perror(argv[0]);
    i = ft_spacelen(cmd) + 1;
    while (cmd[i])
    {
        if (cmd[i] == 123 || cmd[i] == 34 || cmd[i] == 39)
            block = 1;
        if (block && (cmd[i] == '}' || cmd[i] == 34 || cmd[i] == 39))
            block = 0;
        if ((cmd[i] == ' ' && !block) || !cmd[i + 1])
        { 
            argv[j] = ft_substr(cmd, start, i);
            perror(argv[j]);  
            j++;
            i += ft_spacelen(cmd + i);
            start = i + 1;
        }
        i++; 
    }
    argv[i] = NULL;
    return (argv);
}