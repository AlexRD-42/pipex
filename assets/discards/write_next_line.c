/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/11 12:22:06 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

static
size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != 0)
		length++;
	return (length);
}

// static
// uint8_t	is_eof(const char *str, const char *eof)
// {
// 	while (*eof != 0)
// 	{
// 		if (*str++ != *eof++)
// 			return (0);
// 	}
// 	return (*str == 0 || *str == '\n');
// }

static
uint8_t	is_eof(const char *str, const char *eof)
{
	while (*eof != 0 && *str != *eof)
	{
		str++;
		eof++;
	}
	return (*eof == 0 && (*str == 0 || *str == '\n'));
}

static
uint8_t	buffer_scan(char *buffer, int fd_write, const char *eof, size_t bytes_read)
{
	size_t	index;
	size_t	start;
	uint8_t	found_eof;

	index = 0;
	found_eof = 0;
	while (index < (size_t) bytes_read && !found_eof)
	{
		start = index;
		while (buffer[index] != '\n' && index < (size_t) bytes_read)
			index++;
		index += (buffer[index] == '\n');
		found_eof = is_eof(buffer + start, eof);
	}
	if (found_eof == 1)
	{
		write(fd_write, buffer, start);
		return (1);
	}
	return (0);
}

// Start by filling the two buffers with read
// Read from first buffer until buffer_size + EOF_LEN, guaranteeing alias free checks
// If not found, we can safely write knowing there were no EOF in between
// Then copy buffer 1 to buffer 0, fill buffer 1, and repeat
int	write_next_line(int fd_read, int fd_write, const char *eof)
{
	char			buffer[2][BUFFER_SIZE];
	ssize_t			bytes_read;
	const size_t	eof_len = ft_strlen(eof) + 1;

	if (fd_read < 0 || fd_write < 0)
		return (-1);
	bytes_read = read(fd_read, (char *) buffer, BUFFER_SIZE << 1);
	if (bytes_read > BUFFER_SIZE)
		bytes_read = BUFFER_SIZE;
	while (bytes_read > 0)
	{
		if (buffer_scan(buffer[0], fd_write, eof, (size_t) bytes_read + eof_len + 1))
			return (0);
		write(fd_write, buffer[0], BUFFER_SIZE);
		ft_memcpy(buffer[0], buffer[1], BUFFER_SIZE);
		bytes_read = read(fd_read, buffer[1], BUFFER_SIZE);
	}
	return (1);
}
