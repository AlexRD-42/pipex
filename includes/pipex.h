/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:34:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/12 14:31:01 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdint.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <linux/limits.h>

# ifndef FT_ARG_MAX
#  if ARG_MAX > 131072
#   define FT_ARG_MAX 131072
#  else
#   define FT_ARG_MAX ARG_MAX
#  endif
# endif

# ifndef PAGE_SIZE
#  define PAGE_SIZE 4096
# endif

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

void	*ft_memcpy(void *dst_void, const void *src_void, size_t length);
void	*ft_memset(void *dst_void, const uint8_t byte, size_t length);
int32_t	ft_strcmp(const char *str1, const char *str2);
char	*get_next_line(int fd);
int		pipe_exec(char *cmd, char **envp);
int		ft_pipe_loop(size_t argc, char **argv, char **envp, int *fd);
size_t	ft_strlen(const char *str);
int		here_doc(const char *eof);
#endif
