/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:03:00 by rafael-m          #+#    #+#             */
/*   Updated: 2025/06/04 15:17:45 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

typedef struct s_pipex
{
    char    *cmd1;
    char    *cmd2;
    char    *cmd1_path;
    char    *cmd2_path;
    char    *infile;
    char    *outfile;
    char    **envp;
}   t_pipex;

#endif
