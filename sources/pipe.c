/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:45:20 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/10 20:04:22 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm-generic/errno-base.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"
#include <errno.h>

// State[0]: {in_file, 			fd_write_end(0)}
// State[1]: {fd_read_end(0),	fd_write_end(1)}
static
int	ft_child(char *cmd, int fd_read, int fd_write, char **envp)
{
	int	dup2_error;

	dup2_error = dup2(fd_write, STDOUT_FILENO);
	close(fd_read);
	close(fd_write);
	if (dup2_error == -1)
	{
		perror("dup2");
		exit(1);
	}
	pipe_exec(cmd, envp);
	if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

// State[0]: {fd_read_end(0), stdout}
// State[1]: {fd_read_end(1), stdout}
static
int	ft_parent(int fd_read, int fd_write, pid_t pid)
{
	int	status;
	int	dup2_error;
	int	waitpid_error;

	dup2_error = dup2(fd_read, STDIN_FILENO);
	close(fd_read);
	close(fd_write);
	if (dup2_error == -1)
		perror("dup2");
	waitpid_error = waitpid(pid, &status, 0);
	if (waitpid_error == -1)
		perror("waitpid");
	if (waitpid_error == -1 || dup2_error == -1)
		return (-1);
	else
		return ((status & 0xff00) >> 8);
}

// fd[0] read_end, fd[1] write_end
int	ft_pipe(char *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		return (ft_child(cmd, fd[0], fd[1], envp));
	else
		return (ft_parent(fd[0], fd[1], pid));
}
