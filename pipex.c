#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

size_t ft_strlen(char *s)
{
    int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)c == *s)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == *s)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	char		*dest;
	size_t		size;

	size = ft_strlen(src);
	dest = (char *)ft_calloc((size + 1), sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, size + 1);
	return (dest);
}

int ft_child(char *cmd1, char *file1, int pipefd[1])
{
    char buffer;
    ssize_t bytes_read;
    char    *pathname;

    if (ft_strchr(cmd1, '/'))
        pathname = cmd1;
    else
        pathname = ft_strdup("/bin:usr/bin");
    if (!(access(pathname, X_OK)))
            return (-1);
    execve(pathname, );
    bytes_read = read(pipefd[0], &buffer, 1);
    while (bytes_read > 0)
    {
        bytes_read = read(pipefd[0], &buffer, 1);
    }
}

int ft_parent()
{

}

int ft_pipex(char *cmd1, char *cmd2, char *file1, char *file2)
{
    int pipefd[2];
    pid_t   pid;


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
        ft_child(cmd1, file1, pipefd[1]);
    if (pid == 0)
        ft_parent(cmd2, file2, pipefd[0]); 
}

int main(int argc, char **argv)
{
    char *cmd1;
    char *cmd2;
    char *file1;
    char *file2;

    if (argc != 5)
    {
        write(2, "Error: 4 arguments needed in the form of: file1 cmd1 | cmd2 > file2\n", 68);
        return (1);
    }
    cmd1 = (char *)malloc(ft_strlen(argv[2]));
    cmd2 = (char *)malloc(ft_strlen(argv[3]));
    file1 = (char *)malloc(ft_strlen(argv[4]));
    file2 = (char *)malloc(ft_strlen(argv[5]));
    ft_pipex(cmd1, cmd2, file1, file2);
}