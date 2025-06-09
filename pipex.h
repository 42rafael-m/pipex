/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:00 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 15:56:38 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	*cmd1;
	char	*cmd2;
	char	*cmd1_path;
	char	*cmd2_path;
	char	*infile;
	char	*outfile;
}	t_pipex;

int		ft_parent(t_pipex *pipex, int *pipefd, char **envp);
void	ft_free_child_in(t_pipex *pipex);
void	ft_free_child_out(t_pipex *pipex);
int		ft_child(t_pipex *pipex, int *pipefd, char **envp);
int		ft_pipe_fork(t_pipex *pipex, char **envp);
char	*ft_cmd_path(char *env_path, char *cmd);
void	ft_free_node(t_pipex *pipex);
void	ft_error_exit(char *error);
void	ft_write_cmd_error(char *cmd);
char	*ft_parse_pwd(char *s, char **env);
char	*ft_load_line(char *cmd, int start, size_t len);
char	**ft_load_argv(char **argv, char *cmd);
int		ft_spaces(char *str);
size_t	ft_spacelen(char *s);
char	**ft_argv(char *cmd);

#endif
