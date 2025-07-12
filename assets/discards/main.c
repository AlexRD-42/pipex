/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/12 13:06:22 by adeimlin         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	const int	cmd_count = pipex_init(argv, argc, fd) + 2;

	if (cmd_count == -1)
		return (1);
	return (ft_pipe_loop((size_t) (argc - cmd_count), argv + cmd_count, envp, fd));
}
