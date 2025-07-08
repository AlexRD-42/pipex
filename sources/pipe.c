/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:45:20 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/08 11:57:49 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"

static
int	ft_child(char *cmd, int fd_in, int fd_out, char **envp)
{
	close(fd_in);
	dup2(fd_out, 1);
	pipe_exec(cmd, envp);
	return (1);
}

static
int	ft_parent(int fd_in, int fd_out)
{
	close(fd_out);
	dup2(fd_in, 0);
	return (0);
}

int	ft_pipe(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		return (ft_child(cmd, fd[0], fd[1], envp));
	else
		return (ft_parent(fd[0], fd[1]));
}
