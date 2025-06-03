/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:27 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/03 19:39:49 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	ft_parent(char *outfile, int pipefd, char *cmd, char *p, char **envp)
{
	int	outfd;
	char	**argv;

	outfd = open(outfile, O_WRONLY);
	if (outfd == -1)
		return (free(p), perror("open"), errno);
	if (dup2(pipefd, STDIN_FILENO) == -1)
		return (close(pipefd), free(p), perror("dup2"), errno);
	close(pipefd);
	if (dup2(outfd, STDOUT_FILENO) == -1)
		return (close(outfd), free(p), perror("dup2"), errno);
	close(outfd);
	argv = ft_split(cmd, ' ');
	if (!argv)
		return (free(cmd_p), perror("malloc"), errno);
	if (execve(cmd_p, argv, env) == -1)
		return (ft_free_d(argv), free(cmd_p), perror("execve"), errno);
	return (errno);
}
int	ft_child(char *infile, int pipefd, char *cmd, char *cmd_p, char **env)
{
	int	infd;
	char	**argv;

	infd = open(infile, O_RDONLY);
	if (infd == -1)
		return (free(cmd_p), perror("open"), errno);
	if (dup2(infd, STDIN_FILENO) == -1)
		return (close(infd), free(cmd_p), perror("dup2"), errno);
	close(infd);
	if (dup2(pipefd, STDOUT_FILENO) == -1)
		return (close(pipefd), free(cmd_p), perror("dup2"), errno);
	close(pipefd);
	argv = ft_split(cmd, ' ');
	if (!argv)
		return (free(cmd_p), perror("malloc"), errno);
	if (execve(cmd_p, argv, env) == -1)
		return (ft_free_d(argv), free(cmd_p), perror("execve"), errno);
	return (errno);
}

int	ft_pipe_fork(char *infile, char *outfile, char *p1, char *p2, char *cmd1, char *cmd2, char **envp)
{
	int	pipefd[2];
	int	pid;
	int	status;
	int	child;

	if (pipe(pipefd) == -1)
		return (free(p1), free(p2), perror("pipe"), exit(errno), 1);
	pid = fork();
	if (pid == -1)
		return (free(p1), free(p2), perror("fork"), exit(errno), 1);
	if (pid == 0)
		ft_child(infile, pipefd[1], cmd1, p1, envp);
	if (waitpid(pid, &status, 0) == -1)
		return (free(p1), free(p2), perror("wait"), exit(errno), 1);
	if (!ft_parent(outfile, pipefd[0], cmd2, p2, envp))
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (free(p1), free(p2), perror("dup2"), exit(errno), 1);
	infile = open(infile, )
}

char	*ft_cmd_s(char *cmd)
{
	char    *pos;
	char	*r;

	pos = ft_strchr(cmd, ' ');
	if (pos)
 		cmd_s = ft_substr(0, cmd - pos);
	else
		cmd_s = ft_substr(0, ft_strlen(cmd));
 	if (!cmd_s)
		return (perror("malloc"), NULL);
	if (ft_strchr(cmd_s, '/'))
	{
		if (access(cmd, X_OK) == -1)
			return (perror("access"), NULL);
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
	cmd_s = ft_cmd_s(cmd);
	if (!cmd_s || (ft_strchr(cmd_s, '/') && (access(cmd_s, X_OK) == -1)))
		return (NULL);
	if (ft_strchr(cmd_s, '/') && !access(cmd_s, X_OK))
		return (cmd_s);
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH") && !ft_strstr(env[i], "_PATH"))
		{
			cmd_path = ft_strjoin(env[i] + 5, file);
			if (!cmd_path)
				return (perror("malloc"), NULL);
			break ;
		}
		i++;
	}
	if (access(cmd_path, X_OK) == -1)
		return (free(cmd_path), perror("access"), NULL);
	return (cmd_path);
}

int	ft_parse_file(char *file, char **env, int mode)
{
	int	i;
	int	aacc;
	char	*t;
	char	*file_path;

	i = 0;
	if (ft_strchr(file, '/'))
		return (access(file, mode));
	while (env[i])
	{
		if ((ft_strstr(env[i]), "PWD") && !ft_strstr(env[i], "OLDPWD"))
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
	int	status;
	char	*p1;
	char    *p1;
	int	status;

	status = 0;
	if (argc != 5)
		return (write(2, "file1 cmd1 cmd2 file2", 21), 1);
	if (ft_parse_file(argv[1], R_OK) == -1)
		return(perror("access"), errno);
	if (ft_parse_file(argv[4], W_OK) == -1)
		status++;
	p1 = ft_parse_cmd(argv[2], envp);
	p2 = ft_parse_cmd(argv[3], envp);
	status = ft_pipe_fork(infile, outfile, p1, p2, argv[2], argv[3], envp);
	return (free(cmd1_path), free(cmd2_path), status);
}
