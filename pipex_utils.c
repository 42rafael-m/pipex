/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:13 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 16:05:14 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

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
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		ft_error_exit("pipe", pipex);
	pid = fork();
	if (pid == -1)
		ft_error_exit("fork", pipex);
	if (pid == 0 && pipex -> cmd1)
		ft_child_in(pipex, pipefd, envp);
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
