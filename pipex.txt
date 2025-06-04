/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:27 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/04 18:23:52 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	ft_free_node(t_pipex *pipex)
{
	if (pipex -> cmd1)
		free(pipex -> cmd1);
	if (pipex -> cmd2)
		free(pipex -> cmd2);
	if (pipex -> infile)
		free(pipex -> infile);
	if (pipex -> outfile)
		free(pipex -> outfile);
	if (pipex -> cmd1_path)
		free(pipex -> cmd1_path);
	if (pipex -> cmd2_path)
		free(pipex -> cmd2_path);
	free(pipex);
	pipex = NULL;
}

void	ft_error_exit(char *error)
{
	perror(error);
	exit(errno);
}

int	ft_parent(t_pipex *pipex, int pipefd, char **envp)
{
	int		outfd;
	char	**argv;

	outfd = open(pipex -> outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (outfd == -1)
		perror("open");
	if (dup2(pipefd, STDIN_FILENO) == -1)
		perror("dup2");
	close(pipefd);
	if (dup2(outfd, STDOUT_FILENO) == -1)
		perror("dup2");
	close(outfd);
	argv = ft_split(pipex -> cmd2, ' ');
	if (!argv)
		perror("malloc");
	if (execve(pipex -> cmd2_path, argv, envp) == -1)
		perror("execve");
	return (ft_free_d(argv), errno);
}

int	ft_child(t_pipex *pipex, int pipefd, char **envp)
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
	if (dup2(pipefd, STDOUT_FILENO) == -1)
		ft_error_exit("dup2");
	if (close(pipefd) == -1)
		ft_error_exit("close");
	argv = ft_split(pipex -> cmd1, ' ');
	if (!argv)
		ft_error_exit("malloc");
	execve(pipex -> cmd1_path, argv, envp);
	ft_free_d(argv);
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
		ft_error_exit("fork"), exit(errno);
	if (pid == 0 && pipex -> cmd1)
		ft_child(pipex, pipefd[1], envp);
	if (waitpid(pid, &status, 0) == -1)
		ft_error_exit("wait");
	if (close(pipefd[1]) == -1)
		ft_error_exit("close");
	if (pipex -> cmd2)
		ft_parent(pipex, pipefd[0], envp);
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
			return (cmd_path);
		}
		i++;
	}
	return (NULL);
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

t_pipex	*ft_load_node(char	*inf, char *outf, char *cmd1, char *cmd2)
{
	t_pipex	*pipex;
	
	pipex = (t_pipex  *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex -> cmd1_path = NULL;
	pipex -> cmd2_path = NULL;
	pipex -> cmd2 = NULL;
	pipex -> infile = NULL;
	pipex -> outfile = NULL;
	pipex -> cmd1 = ft_strdup(cmd1);
	if (!pipex -> cmd1)
		return (free(pipex), NULL);
	pipex -> cmd2 = ft_strdup(cmd2);
	if (!pipex -> cmd2)
		return (ft_free_node(pipex), NULL);
	pipex -> infile = ft_strdup(inf);
	if (!pipex -> infile)
		return (ft_free_node(pipex), NULL);
	pipex -> outfile = ft_strdup(outf);
	if (!pipex -> outfile)
		return (ft_free_node(pipex), NULL);
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	
	if (argc != 5)
		return (write(2, "file1 cmd1 cmd2 file2", 22), 1);
	pipex = ft_load_node(argv[1], argv[4], argv[2], argv[3]);
	if (!pipex)
		return (perror("malloc"), 1);
	if (ft_parse_file(pipex -> infile, envp, R_OK) == -1)
		return(perror("access"), errno);
	if (ft_parse_file(pipex -> outfile, envp, W_OK) == -1)
		perror("access");
	pipex -> cmd1_path = ft_parse_cmd(pipex -> cmd1, envp);
	if (access(pipex -> cmd1_path, X_OK) == -1)
		perror("access");
	pipex -> cmd2_path = ft_parse_cmd(pipex -> cmd2, envp);
	if (access(pipex -> cmd2_path, X_OK) == -1)
		perror("access");
	ft_pipe_fork(pipex, envp);
	ft_free_node(pipex);
	return (errno);
}
