/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/07 17:13:29 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "pipex.h"

#define PATH_MAX 4096

static const
char	*find_path(char **envp, const char *default_path)
{
	if (envp == NULL)
		return (default_path);
	while (*envp != NULL && !((*envp)[0] == 'P' && (*envp)[1] == 'A' 
		&& (*envp)[2] == 'T' && (*envp)[3] == 'H' && (*envp)[4] == '='))
	{
		envp++;
	}
	if (*envp == NULL)
		return (default_path);
	else
		return (*envp + 5);
}

static
void	exec_cmd(char *cmd, const char *path, char **argv, char **envp)
{
	char	buffer[PATH_MAX];
	size_t	i;
	size_t	j;

	while (*path != 0)
	{
		i = 0;
		while (path[i] != 0 && path[i] != ':')
			i++;
		if (i == 0)
			buffer[i++] = '.';
		else
			ft_memcpy(buffer, path, i);
		path += i + (path[i] == ':');
		buffer[i++] = '/';
		j = 0;
		while (cmd[j] != 0)
			j++;
		ft_memcpy(buffer + i, cmd, j + 1);
		execve(buffer, argv, envp);
	}
}

// Uses 36kb of stack, but avoids the use of malloc
int	pipe_exec(char *cmd, char **envp)
{
	const char	*path = find_path(envp, "/bin:/usr/bin::");

	in_place_split(cmd, buffer);
	exec_cmd(buffer[0], path, buffer, envp);
}

int main(int argc, char **argv, char **envp)
{
	pipe_exec(argv[1], envp);
}
