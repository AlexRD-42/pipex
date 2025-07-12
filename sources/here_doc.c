/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:16:19 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/12 16:47:28 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm-generic/errno-base.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"

static inline
uint8_t	eof_cmp(const char *str, const char *eof)
{
	while (*str == *eof && *eof != 0)
	{
		str++;
		eof++;
	}
	return (*eof == 0 && (*str == 0 || *str == '\n'));
}

// Can be optimized to search for first /n prior to length
size_t	is_eof(const char *str, const char *eof, size_t eof_len, size_t length)
{
	size_t	i;

	i = 0;
	if (length <= eof_len)
		return (0);
	length -= eof_len;
	while (i < length)
	{
		if (eof_cmp(str + i, eof) == 1)
			return (i);
		i++;
	}
	return (0);
}

int	write_to_buffer(char *buffer, size_t length)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	write(fd[1], buffer, length);
	close(fd[1]);
	return (fd[0]);
}

int	here_doc(const char *eof)
{
	ssize_t			bytes_read;
	size_t			offset;
	const size_t	eof_length = ft_strlen(eof);
	char			buffer[65536];
	size_t			length;

	offset = 0;
	bytes_read = read(STDIN_FILENO, buffer, PAGE_SIZE);
	while (bytes_read > 0 && offset < 65536 - PAGE_SIZE)
	{
		offset += (size_t) bytes_read;
		length = is_eof(buffer, eof, eof_length, offset);
		if (length != 0)
			return (write_to_buffer(buffer, length));
		bytes_read = read(STDIN_FILENO, buffer + offset, PAGE_SIZE);
	}
	length = is_eof(buffer, eof, eof_length, offset);
	if (length != 0)
		return (write_to_buffer(buffer, length));
	return (-1);
}
