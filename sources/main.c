/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/11 19:17:52 by adeimlin         ###   ########.fr       */
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
int	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	size_t		i;
	int			input;
	int			output;
	pid_t		cpid[1024];
	const int	is_here_doc = pipex_init(argv, argc, &input, &output);

	if (is_here_doc == -1)
		return (1);
	i = 2 + (size_t) is_here_doc;
	if (ft_dup2(input, STDIN_FILENO) == 1)
		return (1);
	close(input);
	while (i < (size_t)(argc - 2))
	{
		if (ft_pipe(argv[i], envp, cpid + i) == -1)
			return (1);
		i++;
	}
	if (ft_dup2(output, STDOUT_FILENO) == 1)
		return (1);
	close(output);
	while (i > 2 + (size_t) is_here_doc)
		waitpid(cpid[--i], 0, 0);
	pipe_exec(argv[argc - 2], envp);
	return (127);
}
