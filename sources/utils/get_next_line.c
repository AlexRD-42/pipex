/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:07:58 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/10 20:04:12 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

static
void	*gnl_memcpy(void *dst_void, const void *src_void, size_t length)
{
	char		*dst;
	const char	*src = (const char *) src_void;

	dst = (char *) dst_void;
	while (length > 0 && ((uintptr_t)dst & (sizeof(uintptr_t) - 1)))
	{
		*dst++ = *src++;
		length--;
	}
	if (((uintptr_t)src & (sizeof(uintptr_t) - 1)) == 0)
	{
		while (length >= sizeof(uintptr_t))
		{
			*((uintptr_t *)dst) = *((const uintptr_t *)src);
			dst += sizeof(uintptr_t);
			src += sizeof(uintptr_t);
			length -= sizeof(uintptr_t);
		}
	}
	while (length > 0)
	{
		*dst++ = *src++;
		length--;
	}
	return (dst_void);
}

static
char	*append_str(void *str, void *new_str, size_t len, size_t new_len)
{
	char	*dst;

	dst = (char *) malloc (len + new_len + 1);
	if (dst != NULL)
	{
		if (str != NULL)
			gnl_memcpy(dst, str, len);
		gnl_memcpy(dst + len, new_str, new_len);
		dst[len + new_len] = 0;
	}
	free(str);
	return (dst);
}

static
ssize_t	ft_read(int fd, char *buffer, size_t *index, size_t *start)
{
	static ssize_t	bytes_read = 0;

	if (*index >= (size_t) bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
			*index = 0;
		else if (bytes_read < 0)
		{
			bytes_read = 0;
			*start = 1;
			*index = 0;
			return (bytes_read);
		}
	}
	*start = *index;
	while (buffer[*index] != '\n' && *index < (size_t) bytes_read)
		(*index)++;
	*index += (*index < (size_t) bytes_read && buffer[*index] == '\n');
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE] = {0};
	static size_t	index = 0;
	char			*str;
	size_t			length;
	size_t			start;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = NULL;
	length = 0;
	while (ft_read(fd, buffer, &index, &start) > 0)
	{
		str = append_str(str, buffer + start, length, index - start);
		length += index - start;
		if (str == NULL || str[length - 1] == '\n')
			break ;
	}
	if (start > index)
	{
		free(str);
		str = NULL;
	}
	return (str);
}
