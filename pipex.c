/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:48:27 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 17:38:09 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

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
		t = ft_strjoin(path[i], "/");
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

static char	*ft_parse_cmd(char *cmd, char **env)
{
	char	*cmd_path;
	char	*cmd_s;
	int		i;

	i = 0;
	if (cmd && ft_strnchr(cmd, '/', ft_spacelen(cmd)))
		return (cmd);
	cmd_s = ft_substr(cmd, 0, ft_spacelen(cmd));
	if (!cmd_s)
		return (perror("malloc"), NULL);
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH") && !ft_strstr(env[i], "_PATH"))
		{
			cmd_path = ft_cmd_path(env[i] + 5, cmd_s);
			return (free(cmd_s), cmd_path);
		}
		i++;
	}
	return (free(cmd_s), NULL);
}

static int	ft_parse_file(char *file, char **env, int mode)
{
	int		i;
	int		acc;
	char	*t;
	char	*file_path;

	i = 0;
	if (file && ft_strchr(file, '/'))
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
	return (free(file_path), acc);
}

static t_pipex	*ft_load_node(char *inf, char *outf, char *cmd1, char *cmd2)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
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
	int		status;

	if (argc != 5)
		return (write(2, "file1 cmd1 cmd2 file2", 22), 1);
	pipex = ft_load_node(argv[1], argv[4], argv[2], argv[3]);
	if (!pipex)
		return (perror("malloc"), errno);
	if (ft_parse_file(pipex -> infile, envp, R_OK) == -1)
		return (perror(pipex -> infile), ft_free_node(pipex), errno);
	if (ft_parse_file(pipex -> outfile, envp, W_OK) == -1)
		perror(pipex -> outfile);
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
	status = ft_pipe_fork(pipex, envp);
	ft_free_node(pipex);
	return (status);
}
