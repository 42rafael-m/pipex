/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:13 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/05 11:30:59 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	ft_parent(t_pipex *pipex, int *pipefd, char **envp)
{
	int		outfd;
	char	**argv;

	outfd = open(pipex -> outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfd == -1)
		ft_error_exit("open");
	if (dup2(outfd, STDOUT_FILENO) == -1)
		ft_error_exit("dup2");
	if (close(outfd) == -1)
		ft_error_exit("close");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_error_exit("dup2");
	if (close(pipefd[0]) == -1)
		ft_error_exit("close");
	if (close(pipefd[1]) == -1)
		ft_error_exit("close");
	argv = ft_split(pipex -> cmd2, ' ');
	if (!argv)
		ft_error_exit("malloc");
	execve(pipex -> cmd2_path, argv, envp);
	perror("execve");
	return (ft_free_d(argv), errno);
}

void	ft_free_child(t_pipex *pipex)
{
	if (pipex -> cmd1)
		free(pipex -> cmd1);
	if (pipex -> cmd1_path)
		free(pipex -> cmd1_path);
	if (pipex -> infile)
		free(pipex -> infile);
}

int	ft_child(t_pipex *pipex, int *pipefd, char **envp)
{
	int		infd;
	char	**argv;

	infd = open(pipex -> infile, O_RDONLY);
	if (infd == -1)
		ft_error_exit("open");
	if (dup2(infd, STDIN_FILENO) == -1)
		ft_error_exit("dup2");
	if (close(infd) == -1)
		ft_error_exit("close");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error_exit("dup2");
	if (close(pipefd[1]) == -1)
		ft_error_exit("close");
	if (close(pipefd[0]) == -1)
		ft_error_exit("close");
	argv = ft_split(pipex -> cmd1, ' ');
	if (!argv)
		ft_error_exit("malloc");
	execve(pipex -> cmd1_path, argv, envp);
	ft_free_d(argv);
	ft_free_child(pipex);
	ft_error_exit("execve");
	return (ft_free_d(argv), errno);
}

int	ft_pipe_fork(t_pipex *pipex, char **envp)
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		ft_error_exit("pipe");
	pid = fork();
	if (pid == -1)
		ft_error_exit("fork");
	if (pid == 0 && pipex -> cmd1)
		ft_child(pipex, pipefd, envp);
	if (wait(&status) == -1)
		ft_error_exit("wait");
	if (pipex -> cmd2)
		ft_parent(pipex, pipefd, envp);
	return (errno);
}

char	*ft_cmd_path(char *env_path, char *cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;
	char	*t;

	i = 0;
	path = ft_split(env_path, ':');
	if (!path)
		return (perror("malloc"), NULL);
	while (path[i])
	{
		t = ft_strjoin(path[i] + 5, "/");
		if (!t)
			return (ft_free_d(path), perror("malloc"), NULL);
		cmd_path = ft_strjoin(t, cmd);
		free(t);
		if (!cmd_path)
			return (ft_free_d(path), perror("malloc"), NULL);
		if (!access(cmd_path, X_OK))
			return (ft_free_d(path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_d(path), NULL);
}
