#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
//#include "pipex.h"
#include <stdio.h>
#include "libft.h"

char    **ft_path(char **envp)
{
    int i;
    char    **path;
    char    *s;

    i = 0;
    path = NULL;
    while (envp[i])
    {
        s = ft_strstr(envp[i], "PATH");
        if (s && envp[i][0] == 'P')
		    path = ft_split(envp[i] + 5, ':');
        i++;
    }
    return (path);
}

char *ft_access_path(char **path, char *cmd)
{
    int i;
    char    *s;
    char    *t;
    char    *pos;
    char    *pathname;

    i = 0;
    pos = ft_strchr(cmd, ' ');
    if (pos)
        t = ft_substr(cmd, 0, pos - cmd);
    else
        t = ft_substr(cmd, 0, ft_strlen(cmd));
    while (path[i])
    {
        s = ft_strjoin(path[i], "/");
        pathname = ft_strjoin(s, t);
        //printf("pathname = %s\n", pathname);
        free(s);
        s = NULL;
        //printf("access = %i\n", access(pathname, X_OK));
        if (!access(pathname, X_OK))
            return(free(t), t = NULL, pathname);
        free(pathname);
        pathname = NULL;
        i++;
    }
    free(t);
    t = NULL;
    return (NULL);
}

int ft_child(char *cmd1, char *file1, int writefd, char *pathname, char **envp)
{
    char buffer;
    ssize_t bytes_read;
    char    **argv;

    argv = ft_split(cmd1, ' ');
    execve(pathname, argv, envp);
}

int ft_parent()
{

}

int ft_pipex(char *cmd1, char *cmd2, char *file1, char *file2, char **path, char **envp)
{
    int pipefd[2];
    pid_t   pid;
    char    *pathname1;
    char    *pathname2;

    pathname1 = ft_access_path(path, cmd1);
    pathname2 = ft_access_path(path, cmd2);
    if (!(pathname1 || pathname2))
            return (0);
    if (pipe(pipefd) == -1)
    {
       perror("pipe");
       exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
    {
       perror("fork");
       exit(EXIT_FAILURE);
    }
    if (pid > 0)
        ft_child(cmd1, file1, pipefd[1], pathname1, envp);
    ft_parent(cmd2, file2, pipefd[0], pathname2, envp); 
}

int main(int argc, char **argv, char **envp)
{
    char    *cmd1;
    char    *cmd2;
    char    *file1;
    char    *file2;
    char    **path;

	int	i = 0; 
    // if (argc != 5)
    // {
    //      write(2, "Error: 4 arguments needed in the form of: file1 cmd1 | cmd2 > file2\n", 68);
    //      return (1);
    // }
    cmd1 = argv[2];
    cmd2 = argv[3];
    file1 = argv[4];
    file2 = argv[5];
    path = ft_path(envp);
    // while (*envp != NULL)
    // {
    //     printf("%s\n", *envp);
    //     envp++;
    // }
    ft_pipex(cmd1, cmd2, file1, file2, path, envp);
}