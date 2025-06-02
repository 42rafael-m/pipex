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

    i = 0;
    path = NULL;
    while (envp[i])
    {
        if (ft_strstr(envp[i], "PATH"))
        {
			path = ft_split(envp[i] + 5, ':');

		}
        i++;
    }
    return (path);
}

int ft_child(char *cmd1, char *file1, int writefd, char **envp)
{
    // char buffer;
    // ssize_t bytes_read;
    // char    *path;

    
    // execve(path, );
    // bytes_read = read(writefd, &buffer, 1);
    // while (bytes_read > 0)
    // {
    //     bytes_read = read(writefd, &buffer, 1);
    // }
}

int ft_parent()
{

}

int ft_pipex(char *cmd1, char *cmd2, char *file1, char *file2, char **path)
{
    int pipefd[2];
    pid_t   pid;


    if (!(access(cmd1, X_OK)) || !(access(cmd2, X_OK)))
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
        ft_child(cmd1, file1, pipefd[1], path);
    if (pid == 0)
        ft_parent(cmd2, file2, pipefd[0], path); 
}

int main(int argc, char **argv, char **envp)
{
    char    *cmd1;
    char    *cmd2;
    char    *file1;
    char    *file2;
    char    **path;

	int	i = 0; 
    if (argc != 5)
    {
         write(2, "Error: 4 arguments needed in the form of: file1 cmd1 | cmd2 > file2\n", 68);
         return (1);
    }
    cmd1 = (char *)malloc(ft_strlen(argv[2]));
    cmd2 = (char *)malloc(ft_strlen(argv[3]));
    file1 = (char *)malloc(ft_strlen(argv[4]));
    file2 = (char *)malloc(ft_strlen(argv[5]));
    path = ft_path(envp);
    ft_pipex(cmd1, cmd2, file1, file2, path);
}