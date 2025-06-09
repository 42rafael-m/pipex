/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:23:33 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/09 13:31:54 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

int	ft_spaces(char *str)
{
	int	i;
	int	space;
	int	block;

	i = 0;
	space = 0;
	block = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == 123 || str[i] == 34 || str[i] == 39)
			block = 1;
		if (str[i] == 125 || str[i] == 34 || str[i] == 39)
			block = 0;
		if (str[i] == 32 && !block)
			space++;
		i++;
	}
	return (space);
}

char	*ft_load_line(char *cmd, int start, int i)
{
	char	*t;
	char	*argv;

	if (!cmd)
		return (NULL);
	argv = ft_substr(cmd, start, i);
	if (!argv)
		return (NULL);
	if (ft_strchr(argv, '\'') || ft_strchr(argv, '"'))
	{
		t = argv;
		argv = ft_strtrim(t, "\"'");
		if (!argv)
			return (NULL);
		free (t);
	}
	return (argv);
}

char	**ft_load_argv(char **argv, char *cmd, int i)
{
	int	j;
	int	block;
	int	start;

	j = 1;
	while (cmd[i])
	{
		if (cmd[i] == 123 || cmd[i] == 34 || cmd[i] == 39)
			block = 1;
		if (block && (cmd[i] == '}' || cmd[i] == 34 || cmd[i] == 39))
			block = 0;
		if ((cmd[i] == ' ' && !block) || !cmd[i + 1])
		{
			argv[j] = ft_load_line(cmd, start, i);
			if (!argv[j])
				return (ft_free_d(argv), NULL);
			i += ft_spacelen(cmd + i);
		}
		i++;
		start = i + 1;
		j++;
	}
	argv[i] = NULL;
	return (argv);
}

char	**ft_argv(char *cmd)
{
	char	**argv;
	int		space;
	int		start;
	int		i;

	i = ft_spacelen(cmd) + 1;
	if (i < 0)
		return (NULL);
	space = ft_spaces(cmd);
	start = ft_spacelen(cmd) + 1;
	if (!ft_strchr(cmd, 34) && !ft_strchr(cmd, 39) && !ft_strchr(cmd, 123))
		return (ft_split(cmd, ' '));
	argv = (char **)ft_calloc(space + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_substr(cmd, 0, ft_spacelen(cmd));
	if (!argv[0])
		return (NULL);
	argv = ft_load_argv(argv, cmd, i);
	return (argv);
}
