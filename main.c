/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/09 20:28:23 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	if (argc > 4)
	{
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			int fd1[2];
			if (pipe(fd1))
				sys_err_exit("pipe failed");
			while (1)
			{
				char *here_doc = get_next_line(STDIN_FILENO); //leaks here
				if (ft_strcmp(here_doc, argv[2]) == 0)
					break ;
				write(fd[1], here_doc, ft_strlen(here_doc));
			}
			int i = 3;
			while (i < argc)
			{
				pid_t	pid = fork();
				if (pid == (pid_t)0)
				{
					dup2(fd[0], STDIN_FILENO);

				}
				i++;
			}
		}
		else
		{

		}
	}
	return (0);
}
