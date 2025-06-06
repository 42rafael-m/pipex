#include "Libft/libft.h"
#include "pipex.h"

int main()
{
    perror("awk '{printf \$2}'");
    char **argv = ft_argv("awk '{printf \$2}'");
    execve("usr/bin/", argv, 0);
}