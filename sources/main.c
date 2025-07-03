/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:23:48 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/01 16:01:11 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("I am the child process.\n");
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("I am the parent process.\n");
		wait(NULL);
		printf("Child process terminated after a 2s delay.\n");
	}

	return (EXIT_SUCCESS);
}

// int main()
// {
// 	int fd[2];
// 	pid_t pid;
// 	char buffer[13];

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0)
// 	{
// 		close(fd[0]); // close the read end of the pipe
// 		write(fd[1], "Hello parent!", 13);
// 		close(fd[1]); // close the write end of the pipe
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(fd[1]); // close the write end of the pipe
// 		read(fd[0], buffer, 13);
// 		close(fd[0]); // close the read end of the pipe
// 		printf("Message from child: '%s'\n", buffer);
// 		exit(EXIT_SUCCESS);
// 	}
// }