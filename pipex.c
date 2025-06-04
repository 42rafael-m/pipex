/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:27 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/04 13:54:53 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	ft_parent(char *outfile, int pipefd, char *cmd, char *p, char **envp)
{
	int	outfd;
	char	**argv;

	outfd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfd == -1)
		perror("open");
	if (dup2(pipefd, STDIN_FILENO) == -1)
		perror("dup2");
	close(pipefd);
	if (dup2(outfd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(outfd);
	argv = ft_split(cmd, ' ');
	if (!argv)
		perror("malloc");
	if (execve(p, argv, envp) == -1)
		perror("execve");
	return (ft_free_d(argv), free(p), errno);
}
int	ft_child(char *infile, int pipefd, char *cmd, char *cmd_p, char **env)
{
	int	infd;
	char	**argv;

	infd = open(infile, O_RDONLY);
	if (infd == -1)
		perror("open");
	if (dup2(infd, STDIN_FILENO) == -1)
		perror("dup2");
	close(infd);
	if (dup2(pipefd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipefd);
	argv = ft_split(cmd, ' ');
	if (!argv)
		return (free(cmd_p), perror("malloc"), errno);
	if (execve(cmd_p, argv, env) == -1)
		perror("execve");
	return (ft_free_d(argv), free(cmd_p), errno);
}

int	ft_pipe_fork(char *infile, char *outfile, char *p1, char *p2, char *cmd1, char *cmd2, char **envp)
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork"), exit(errno);
	if (pid == 0)
		ft_child(infile, pipefd[1], cmd1, p1, envp);
	if (waitpid(pid, &status, 0) == -1)
		perror("wait");
	close(pipefd[1]);
	ft_parent(outfile, pipefd[0], cmd2, p2, envp);
	return (errno);
}

char	*ft_cmd_path(char *env_path, char *cmd)
{
	int	i;
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
			t = NULL;
			if (!cmd_path)
				return (ft_free_d(path), perror("malloc"), NULL);
			if (!access(cmd_path, X_OK))
				return (ft_free_d(path), cmd_path);
			free(cmd_path);
			cmd_path = NULL;
			i++;
	}
	return (ft_free_d(path), NULL);
}

char	*ft_cmd_s(char *cmd)
{
	char    *pos;
	char	*cmd_s;
	char	*r;

	pos = ft_strchr(cmd, ' ');
	if (pos)
 		cmd_s = ft_substr(cmd, 0, pos - cmd);
	else
		cmd_s = ft_substr(cmd, 0, ft_strlen(cmd));
 	if (!cmd_s)
		return (perror("malloc"), NULL);
	if (ft_strchr(cmd_s, '/'))
	{
		if (access(cmd, X_OK) == -1)
			perror("access");
		r = ft_strdup(cmd);
		if (!r)
			return (free(cmd_s), perror("malloc"), NULL);
		return (free(cmd_s), r);
 	}
	return (cmd_s);
}

char	*ft_parse_cmd(char *cmd, char **env)
{
	char	*cmd_path;
	char	*cmd_s;
	int	i;

	i = 0;
	cmd_path = NULL;
	cmd_s = ft_cmd_s(cmd);
	if (!cmd_s)
		return (NULL);
	if (ft_strchr(cmd_s, '/') && (access(cmd_s, X_OK) == -1))
		return(perror("access"), cmd_s);
	if (ft_strchr(cmd_s, '/') && !access(cmd_s, X_OK))
		return (cmd_s);
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH") && !ft_strstr(env[i], "_PATH"))
		{
			cmd_path = ft_cmd_path(env[i] + 5, cmd_s);
			if (!cmd_path)
				return (perror("malloc"), NULL);	
			break ;
		}
		i++;
	}
	if (access(cmd_path, X_OK) == -1)
		perror("access");
	return (cmd_path);
}

int	ft_parse_file(char *file, char **env, int mode)
{
	int	i;
	int	acc;
	char	*t;
	char	*file_path;

	i = 0;
	if (ft_strchr(file, '/'))
		return (access(file, mode));
	while (env[i])
	{
		if (ft_strstr(env[i], "PWD") && !ft_strstr(env[i], "OLDPWD"))
		{
			t = ft_strjoin(env[i] + 4, "/");
			file_path = ft_strjoin(t, file);
			free(t);
			t = NULL;
		}
		i++;
	}
	acc = access(file_path, mode);
	return(free(file_path), acc);
}

int	main(int argc, char **argv, char **envp)
{
	char	*p1;
	char    *p2;
	
	if (argc != 5)
		return (write(2, "file1 cmd1 cmd2 file2", 22), 1);
	if (ft_parse_file(argv[1], envp, R_OK) == -1)
		return(perror("access"), errno);
	if (ft_parse_file(argv[4], envp, W_OK) == -1)
		perror("access");
	p1 = ft_parse_cmd(argv[2], envp);
	p2 = ft_parse_cmd(argv[3], envp);
	ft_pipe_fork(argv[1], argv[4], p1, p2, argv[2], argv[3], envp);
	return (free(p1), free(p2), errno);
}
