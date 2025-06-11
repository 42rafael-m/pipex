
#include "libft/libft.h"
#include "pipex_bonus.h"

void	ft_child_out(t_pipex *pipex, int *pipefd, char **envp)
{
	int		outfd;
	char	**argv;

	outfd = open(pipex -> outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfd == -1)
		ft_error_exit("open", pipex);
	if (dup2(outfd, STDOUT_FILENO) == -1)
		ft_error_exit("dup2", pipex);
	if (close(outfd) == -1)
		ft_error_exit("close", pipex);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_error_exit("dup2", pipex);
	if (close(pipefd[0]) == -1)
		ft_error_exit("close", pipex);
	if (close(pipefd[1]) == -1)
		ft_error_exit("close", pipex);
	argv = ft_argv(pipex -> cmd2);
	if (!argv)
		ft_error_exit("malloc", pipex);
	execve(pipex -> cmd2_path, argv, envp);
	ft_free_d(argv);
	ft_error_exit("execve", pipex);
}

void	ft_child_in(t_pipex *pipex, int *pipefd, char **envp)
{
	int		infd;
	char	**argv;

	infd = open(pipex -> infile, O_RDONLY);
	if (infd == -1)
		ft_error_exit("open", pipex);
	if (dup2(infd, STDIN_FILENO) == -1)
		ft_error_exit("dup2", pipex);
	if (close(infd) == -1)
		ft_error_exit("close", pipex);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error_exit("dup2", pipex);
	if (close(pipefd[1]) == -1)
		ft_error_exit("close", pipex);
	if (close(pipefd[0]) == -1)
		ft_error_exit("close", pipex);
	argv = ft_argv(pipex -> cmd1);
	if (!argv)
		ft_error_exit("malloc", pipex);
	execve(pipex -> cmd1_path, argv, envp);
	ft_free_d(argv);
	ft_error_exit("execve", pipex);
}

int	ft_pipe_fork(t_pipex *pipex, char **envp)
{
	int	pipefd[2];
	int	pipefd2[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		ft_error_exit("pipe", pipex);
	pid = fork();
	if (pid == -1)
		ft_error_exit("fork", pipex);
	if (pid == 0 && pipex -> cmd1)
		ft_child_in(pipex, pipefd, envp);
	if (pipe(pipefd2) == -1)
		ft_error_exit("pipe", pipex);
	pid = fork();
	if (pid == -1)
		ft_error_exit("fork", pipex);
	if (pid == 0 && pipex -> cmd2)
		ft_child_out(pipex, pipefd, envp);
	if (close(pipefd[1]) == -1)
		ft_error_exit("close", pipex);
	if (close(pipefd[0]) == -1)
		ft_error_exit("close", pipex);
	if (wait(&status) == -1)
		ft_error_exit("wait", pipex);
	if (wait(&status) == -1)
		ft_error_exit("wait", pipex);
	return (status);
}

t_pipex	*ft_load_list(int argc, char **argv, char **envp)
{
	int	n;
	t_pipex	*pipex;
	t_pipex	*t;
	t_pipex	*start;

	n = 0;
	t = NULL;
	while (n <= argc - 4)
	{
		if (n == 0)
		{
			pipex = ft_load_node(argv[1], NULL, argv[2], argv[3]);
			start = pipex;
		}
		else if (n == (argc - 4))
			pipex = ft_load_node(NULL, argv[argc - 1], argv[2], argv[3]);
		else
			pipex = ft_load_node(NULL, NULL, argv[n + 3], argv[n + 4]);
			pipex -> next = t;
		pipex -> cmd1_path = ft_parse_cmd(pipex -> cmd1, envp);
		if (!pipex -> cmd1_path)
			pipex -> cmd1_path = ft_parse_pwd(pipex -> cmd1, envp);
		if (access(pipex -> cmd1_path, X_OK) == -1)
			perror (pipex -> cmd1);
		pipex -> cmd2_path = ft_parse_cmd(pipex -> cmd2, envp);
		if (!pipex -> cmd2)
			pipex -> cmd2_path = ft_parse_pwd(pipex -> cmd2, envp);
		if (access(pipex -> cmd2_path, X_OK) == -1)
			perror (pipex -> cmd2);
		t = pipex;
	}
	pipex -> next = NULL;
	return (start);
}

void	ft_child_middle(t_pipex *pipex, char **envp, int *pipefd, int *pipefd2)
{
	char	**argv;

	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_error_exit("dup2", pipex);
	if (dup2(pipefd2[1], STDOUT_FILENO) == -1)
		ft_error_exit("dup2", pipex);
	if (close(pipefd[0]) == -1)
		ft_error_exit("close", pipex);
	if (close(pipefd[1]) == -1)
		ft_error_exit("close", pipex);
	if (close(pipefd2[0]) == -1)
		ft_error_exit("close", pipex);
	if (close(pipefd2[1]) == -1)
		ft_error_exit("close", pipex);
	argv = ft_argv(pipex -> cmd1);
	if (!argv)
		ft_error_exit("malloc", pipex);
	execve(pipex -> cmd1_path, argv, envp);
	ft_free_d(argv);
	ft_error_exit("execve", pipex);
}