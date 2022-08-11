/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:41:36 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 13:41:48 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

# include "libft/libft.h"

# define GNL_BUF_SIZE 1024 

typedef struct s_str
{
	size_t	len;
	char	*str;
}t_str;

//get_next_line.c
char	*get_next_line(int fd);

//pipe_utils.c
void	sys_err_exit(char *msg);
void	execute_cmd(char *argv, char **envp);

//main.c

//cmd_execution.c
char	*get_pathname(char *envp[], char *cmd);
char	*get_abs_path(char *envp, char *cmd);

#endif
