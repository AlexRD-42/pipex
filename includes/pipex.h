/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:34:28 by adeimlin          #+#    #+#             */
/*   Updated: 2025/07/08 12:33:26 by adeimlin         ###   ########.fr       */
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
#  define FT_ARG_MAX ARG_MAX
# endif

# if FT_ARG_MAX > 131072
#  undef FT_ARG_MAX
#  define FT_ARG_MAX 131072
# endif

void	*ft_memcpy(void *dst_void, const void *src_void, size_t length);
void	*ft_bzero(void *dst_void, size_t length);
void	*ft_memset(void *dst_void, const uint8_t byte, size_t length);
int		pipe_exec(char *cmd, char **envp);
int		ft_pipe(char *cmd, char **envp);

#endif
