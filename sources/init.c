/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:16:19 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/12 12:29:56 by adeimlin         ###   ########.fr       */
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
uint8_t	is_eof(const char *str, const char *eof)
{
	while (*str == *eof && *eof != 0)
	{
		str++;
		eof++;
	}
	return (*eof == 0 && (*str == 0 || *str == '\n'));
}

int	here_doc(const char *eof)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (is_eof(line, eof))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	return (fd[0]);
}

int	pipex_init(char **argv, int argc, int *fd)
{
	const uint8_t	is_here_doc = ft_strcmp(argv[argc != 1], "here_doc") == 0;

	if (argc <= (4 + is_here_doc))
	{
		write(2, "Pipex: Incorrect argument count\n", 32);
		return (-1);
	}
	if (is_here_doc == 1)
		fd[0] = here_doc(argv[2]);
	else
		fd[0] = open(argv[1], O_RDONLY, 0644);
	if (is_here_doc)
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		close(fd[0]);
		perror("open");
		return (-1);
	}
	return (is_here_doc);
}
