/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_next_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/10 20:04:09 by adeimlin         ###   ########.fr       */
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
int	write_next_line(int fd_read, int fd_write, const char *eof)
{
	static char		buffer[BUFFER_SIZE] = {0};
	size_t			index;
	size_t			start;
	ssize_t			bytes_read;
	uint8_t			found_eof;

	if (fd_read < 0 || fd_write < 0)
		return (-1);
	found_eof = 0;
	while (ft_read(fd_read, buffer, &index, &bytes_read) >= 0)
	{
		while (index < (size_t) bytes_read && !found_eof)
		{
			start = index;
			while (buffer[index] != '\n' && index < (size_t) bytes_read)
				index++;
			index += (buffer[index] == '\n');
			found_eof = ft_strcmp(buffer + start, eof) == 0;
		}
		write(fd_write, buffer, start);
	}
	return (0);
}
