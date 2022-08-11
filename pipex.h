/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:41:36 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 15:02:08 by jiwahn           ###   ########.fr       */
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

typedef struct	s_str
{
	size_t	len;
	char	*str;
}				t_str;

//get_next_line.c
char	*get_next_line(int fd);

//pipe_utils.c
void	sys_err_exit(char *msg);

//here_document.c

//execute_cmd.c
void	execute_cmd(char *argc, char **envp);
char	*get_pathname(char *envp[], char *cmd);
char	*get_abs_path(char *envp, char *cmd);

//main.c
int		main(int argc, char *argv[], char *envp[]);
void	processing();
void	proc_get_infile(int i, int fds[2][2], char *argv[], char *envp[]);
void	proc_make_outfile(int i, int fds[2][2], char *argv[], char *envp[]);
void	proc_piping(int i, int fds[2][2], char *argv, char *envp[]);

#endif
