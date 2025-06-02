/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:02:35 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/02 19:17:43 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **envp)
{
	int	i;
	char	**path;
	char	*s;

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

char	*ft_access_path(char **path, char *cmd)
{
	int	i;
	char	*s;
	char	*t;
	char	*pos;
	char	*pathname;

	i = 0;
	pos = ft_strchr(cmd, ' ');
	if (pos)
		t = ft_substr(cmd, 0, pos - cmd);
	else
		t = ft_substr(cmd, 0, ft_strlen(cmd));
	if (!t)
		return (NULL);
	if (ft_strchr(t, '/'))
	{
		if (access(t, F_OK) == -1)
			return (perror("access"), free (t), t = NULL, NULL);
		if (!access(t, X_OK))
			return (t);
		return (free(t), t = NULL, NULL);
	}
	while (path[i])
	{
		s = ft_strjoin(path[i], "/");
		if (!s)
			return (free(t), t = NULL, NULL);
		pathname = ft_strjoin(s, t);
		if (!pathname)
			return (free(t), t = NULL, free(s), s = NULL, NULL);
		free(s);
		s = NULL;
		if (!access(pathname, X_OK))
			return(free(t), t = NULL, free(s), s = NULL, pathname);
		free(pathname);
		pathname = NULL;
		i++;
	}
	return (free(t), t = NULL, NULL);
}

int	ft_child(char *cmd1, int infile, int *pipefd, char *pathname, char **envp)
{
	char	**argv;

	argv = ft_split(cmd1, ' ');
	if (!argv)
		return (0);
	if(dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (perror("dup2"), ft_free_double_ptr(argv), 0);
	if(dup2(infile, STDIN_FILENO) == -1)
		return (perror("dup2"), ft_free_double_ptr(argv), 0);
	if (close(pipefd[1]) == -1)
		return (perror("close"), ft_free_double_ptr(argv), 0);
	if (close(pipefd[0]) == -1)
		return (perror("close"), ft_free_double_ptr(argv), 0);
	if (execve(pathname, argv, envp) == -1)
		return (perror("execve"), free(pathname), 0);
	return (ft_free_double_ptr(argv), 1);
}

int	ft_parent(char *cmd2, int outfile, int *pipefd, char *pathname, char **envp)
{
	char	**argv;

	argv = ft_split(cmd2, ' ');
	if (!argv)
		return (0);
	if(dup2(pipefd[0], STDIN_FILENO) == -1)
		return (ft_free_double_ptr(argv), perror("dup2"), 0);
	if(dup2(outfile, STDOUT_FILENO) == -1)
		return (ft_free_double_ptr(argv), perror("dup2"), 0);
	if (close(pipefd[1]) == -1)
		return (ft_free_double_ptr(argv), perror("close"), 0);
	if (close(pipefd[0]) == -1)
		return (ft_free_double_ptr(argv), perror("close"), 0);
	if (execve(pathname, argv, envp) == -1)
		return (ft_free_double_ptr(argv), perror("execve"), 0);
	return (ft_free_double_ptr(argv),  1);
}

int	ft_pipex(char *cmd1, char *cmd2, int infile, int outfile, char **path, char **envp)
{
	int	pipefd[2];
	pid_t	pid;
	char	*pathname1;
	char	*pathname2;
	int	status;

	pathname1 = ft_access_path(path, cmd1);
	pathname2 = ft_access_path(path, cmd2);
	if (!pathname1 || !pathname2)
		return (free(pathname1), free(pathname2), write(2, "Command not found: ", 20), write(2, cmd1, ft_strlen(cmd1)), 0);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), free(pathname1), free(pathname2), 0);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(pathname1), free(pathname2), 0);
	if (pid == 0)
	if (!ft_child(cmd1, infile, pipefd, pathname1, envp))
		return (free(pathname1), free(pathname2), 0);
	if (waitpid(pid,&status, 0) == -1)
		return(write(2, "Can´t wait", 12), free(pathname1), free(pathname2), 0);
	if (!ft_parent(cmd2, outfile, pipefd, pathname2, envp))
		return (free(pathname1), free(pathname2), 0);
	return (free(pathname1), free(pathname2),1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd1;
	char	*cmd2;
	int	infile;
	int	outfile;
	char	**path;
 
	if (argc != 5)    
		return (write(2, "Error: expected 4 arguments: file1 cmd1 | cmd2 > file2\n", 56), 1);
	cmd1 = argv[2];
	cmd2 = argv[3];
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (perror("open"), 1);
	outfile = open(argv[4], O_WRONLY);
	if (outfile == -1)
		return (perror("open"), 1);
	path = ft_path(envp);
	if (!path)
		return (write(2, "Invalid path", 13), 1); 
	if ((!ft_pipex(cmd1, cmd2, infile, outfile, path, envp)))
		return (ft_free_double_ptr(path), 1);
	return (ft_free_double_ptr(path), 0);
}
