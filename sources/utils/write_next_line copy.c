/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_next_line copy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/11 11:25:18 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "pipex.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

static inline
ssize_t	ft_read(int fd, char *buffer, size_t *index, ssize_t *bytes_read)
{
	*index = 0;
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	return (*bytes_read);
}

// Reads from the buffer, and writes once it found eof OR buffer_size
// EOF max is str_len
// wow this shit is so stupid why do i do this
// EOF might end up between reads and that shit is annoying to deal with
// Double buffering is the way to go
// You can solve the indexing problem by doing index++ and % 2

static
size_t	buffer_read(char *buffer, int fd, const char *eof)
{
	size_t	index;
	size_t	start;
	ssize_t	bytes_read;
	uint8_t	found_eof;

	index = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (index < (size_t) bytes_read && !found_eof)
	{
		start = index;
		while (buffer[index] != '\n' && index < (size_t) bytes_read)
			index++;
		index += (buffer[index] == '\n');
		found_eof = ft_strcmp(buffer + start, eof) == 0;
	}
	if (found_eof == 1)
		return (start);
	else
		return (0);
}

static
size_t	buffer_scan(char *buffer, int fd, const char *eof)
{
	size_t	index;
	size_t	start;
	ssize_t	bytes_read;
	uint8_t	found_eof;

	index = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (index < (size_t) bytes_read && !found_eof)
	{
		start = index;
		while (buffer[index] != '\n' && index < (size_t) bytes_read)
			index++;
		index += (buffer[index] == '\n');
		found_eof = ft_strcmp(buffer + start, eof) == 0;
	}
	if (found_eof == 1)
		return (start);
	else
		return (0);
}

int	write_next_line(int fd_read, int fd_write, const char *eof)
{
	char	buffer[2][BUFFER_SIZE];
	size_t	index;
	size_t	start;
	ssize_t	bytes_read;

	if (fd_read < 0 || fd_write < 0)
		return (-1);
	start = 0;
	while (start == 0)
	{
		start = buffer_read(buffer[0], fd_read, eof);
		if (start != 0)
		{
			write(fd_write, buffer[0], start);
			return (0);
		}
		read(fd_read, buffer[1], BUFFER_SIZE);
	}
	return (0);
}
