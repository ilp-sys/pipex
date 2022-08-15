/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:41:36 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/15 21:02:20 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

# include "libft/libft.h"

# define TMP_FILE_NAME "pipex_heredoc_tmp"
# define BUFFER_SIZE 1024

typedef struct s_str
{
	int		len;
	char	*str;
}t_str;

typedef struct s_args
{
	int		argc;
	char	**argv;
	char	**envp;
}t_args;

//pipe_utils.c
t_args	set_args(int argc, char *argv[], char *envp[]);
void	err_found_exit(void);
void	close_a_pipe(int fd[2]);
void	free_split(char **split);
void	dup2_try_catch(int fildes, int fildes2);

//execute_cmd.c
void	execute_cmd(char *argc, char **envp);
char	*get_pathname(char *envp[], char *cmd);
char	*get_abs_path(char *envp, char *cmd);

//main.c
int		main(int argc, char *argv[], char *envp[]);
void	processing(int here_doc, int i, t_args args);
void	proc_get_infile(int here_doc, int i, int fds[2][2], t_args args);
void	proc_make_outfile(int here_doc, int i, int fds[2][2], t_args args);
void	proc_piping(int i, int fds[2][2], t_args args);

//here_document.c
void	here_doc_check(int *i, int *here_doc, t_args args);
void	stdin_get_next_line(int fd, char *LIMITER);
char	*get_stdin_heredoc(char *argv[], char *envp[]);

//get_next_line.c
char	*get_next_line(int fd);

#endif
