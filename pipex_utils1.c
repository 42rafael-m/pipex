/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:26:50 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 13:22:45 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

void	ft_error_exit(char *error, t_pipex *pipex)
{
	ft_free_node(pipex);
	perror(error);
	exit(errno);
}

char	*ft_parse_pwd(char *s, char **env)
{
	int		i;
	char	*t;
	char	*s_path;

	i = 0;
	if (ft_strchr(s, '/'))
		return (s);
	while (env[i])
	{
		if (ft_strstr(env[i], "PWD") && !ft_strstr(env[i], "OLDPWD"))
		{
			t = ft_strjoin(env[i] + 4, "/");
			s_path = ft_strjoin(t, s);
			free(t);
			t = NULL;
		}
		i++;
	}
	return (s_path);
}

size_t	ft_spacelen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != ' '))
		i++;
	return (i);
}
