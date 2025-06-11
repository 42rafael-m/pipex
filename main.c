#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex_bonus.h"
# define ESC_CHARS "\\\'\"\?abfnrtv"

int main(int argc, char **argv)
{
    int i = 0;
    char **r = ft_load_mid_cmds(argv, argc);
	while (i < (argc - 5))
	{
		printf("r[%d] = %s\n", i, r[i]);
        if (r[i])
            free(r[i]);
        i++;
	}
    free(r);
}