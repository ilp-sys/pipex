/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:59:26 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/13 17:32:43 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_args	set_args(int argc, char *argv[], char *envp[])
{
	t_args	args;

	args.argc = argc;
	args.argv = argv;
	args.envp = envp;
	return (args);
}

void	err_found_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	close_a_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	split = NULL;
}

void	dup2_try_catch(int fildes, int fildes2)
{
	if (dup2(fildes, fildes2) == -1)
		err_found_exit("dup2 failed");
}
