/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:40:55 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/08 13:44:45 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int argc, char *argv[], char *argp[])
{
	int		fds[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fds))
			return ;

		pid = fork();
		if (pid == (pid_t)0)
		{
			dup2(fd[1], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			execve(); //
		}

		waitpid(pid, NULL, 0);
	}
	return 0;
}
