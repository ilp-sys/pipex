/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:41:36 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/12 18:56:41 by jiwahn           ###   ########.fr       */
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

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
}t_args;

//pipe_utils.c
t_args	set_args(int argc, char *argv[], char *envp[]);
void	err_found_exit(char *msg);
void	close_a_pipe(int fd[2]);

//execute_cmd.c
void	execute_cmd(char *argc, char **envp);
char	*get_pathname(char *envp[], char *cmd);
char	*get_abs_path(char *envp, char *cmd);

//main.c
int		main(int argc, char *argv[], char *envp[]);
void	processing(int i, t_args args);
void	proc_get_infile(int i, int fds[2][2], char *argv[], char *envp[]);
void	proc_make_outfile(int i, int fds[2][2], char *argv[], char *envp[]);
void	proc_piping(int i, int fds[2][2], char *argv[i], char *envp[]);

#endif
