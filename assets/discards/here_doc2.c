/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:16:19 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/11 16:46:16 by adeimlin         ###   ########.fr       */
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
size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != 0)
		length++;
	return (length);
}

static
uint8_t	is_eof(const char *str, const char *eof)
{
	while (*str != *eof && *eof != 0)
	{
		str++;
		eof++;
	}
	return (*eof == 0 && (*str == 0 || *str == '\n'));
}

#define BUFFER_SIZE 32768
#define READ_SIZE 4096

// Child special case
int	here_doc(const char *eof)
{
	char	buffer[BUFFER_SIZE + READ_SIZE];
	int		fd[2];
	ssize_t	bytes_read;
	size_t	offset;
	const size_t	eof_len = ft_strlen(eof);

	bytes_read = 1;
	offset = 0;
	while (bytes_read > 0 && offset < BUFFER_SIZE)
	{
		bytes_read = read(STDIN_FILENO, buffer + offset, READ_SIZE);
		if (bytes_read < 0)
			return (-1);
		offset += (size_t) bytes_read;
		if (is_eof(buffer + offset - eof_len, eof))
			break ;
	}
	if (offset > BUFFER_SIZE)
		write_to_file();
	else

	write(fd[1], line, ft_strlen(line));
	close(fd[1]);
	return (fd[0]);
}
