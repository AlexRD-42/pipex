/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:16:19 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/10 18:51:39 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm-generic/errno-base.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"

static
int	pipex_error(int error_code)
{
	
}

static
int	here_doc(const char *eof, int *fd)
{
	
	return (0);
}

int	pipex_init(char **argv, int argc, int *input, int *output)
{
	const uint8_t	is_here_doc = ft_strcmp(argv[1], "here_doc") == 0;

	if (argc <= 4 + is_here_doc)
		return (pipex_error(1));
	*output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*output == -1)
	{
		perror("open");
		return (-1);
	}
	if (is_here_doc == 1)
		here_doc(argv[2], input);
	else
	{
		*input = open(argv[1], O_RDONLY, 0777);
		if (*input == -1)
		{
			close(*output);
			perror("open");
			return (-1);
		}
	}
	return (0);
}
