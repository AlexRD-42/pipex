/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/10 18:50:25 by adeimlin         ###   ########.fr       */
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
	size_t	i;
	int		input;
	int		output;

	if (pipex_init(argv, argc, &input, &output) != 0)
		return (1);
	i = 2;
	dup2(input, 0);
	while (i < (size_t)(argc - 2))
		ft_pipe(argv[i++], envp);
	dup2(output, 1);
	close(output);
	pipe_exec(argv[argc - 1], envp);
	return (1);
}
