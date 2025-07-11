/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/11 20:21:19 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"
#include <sys/wait.h>

static
int	wait_child(pid_t *pid, size_t length)
{
	int	status;

	waitpid(pid[--length], &status, 0);
	while (length > 0)
	{
		length--;
		if (pid[length] > 0)
			waitpid(pid[length], 0, 0);
	}
	return ((status & 0xff00) >> 8);
}

int	main(int argc, char **argv, char **envp)
{
	size_t		i;
	int			input;
	int			output;
	pid_t		cpid[1024];
	const int	is_here_doc = pipex_init(argv, argc, &input, &output);

	ft_memset(cpid, 0, sizeof(pid_t) * 1024);
	if (is_here_doc == -1)
		return (1);
	i = 2 + (size_t) is_here_doc;
	if (input >= 0)
		dup2(input, STDIN_FILENO);
	close(input);
	while (i < (size_t)(argc - 2))
	{
		ft_pipe(argv[i], envp, cpid + i);
		i++;
	}
	pid_t last;

	last = fork();
	if (last < 0)
	{
		perror("fork");
		close(output);
		return (1);
	}
	if (last == 0)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
		pipe_exec(argv[argc - 2], envp);
	}
	// Parent:
	cpid[i++] = last;
	close(output);
	// ---- ADD THIS LINE ----
	close(STDIN_FILENO);
	// now every reader is gone once the final child exits
	return (wait_child(cpid, i));
}
