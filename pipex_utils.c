/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:59:26 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/12 18:32:16 by jiwahn           ###   ########.fr       */
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
