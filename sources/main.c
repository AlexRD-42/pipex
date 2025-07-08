/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/08 11:22:39 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	const int	fd_in = open(argv[1], O_RDONLY, 0777);
	const int	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);

	dup2(fd_in, 0);
	ft_pipe(argv[2], envp);
	dup2(fd_out, 1);
	ft_pipe(argv[3], envp);
}
