/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/12 18:37:28 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_get_infile(int i, int fds[2][2], char *argv[], char *envp[])
{
	int	infile;

	close(fds[i % 2][0]);
	infile = open(argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO);
	dup2(fds[i % 2][1], STDOUT_FILENO);
	close(infile);
	close(fds[i % 2][1]);
	execute_cmd(argv[i], envp);
}

void	proc_make_outfile(int i, int fds[2][2], char *argv[], char *envp[])
{
	close(fds[i % 2][0]);
	close(fds[!(i % 2)][1]);
	dup2(fds[i % 2][1], STDOUT_FILENO);
	dup2(fds[!(i % 2)][0], STDIN_FILENO);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][0]);
	execute_cmd(argv[i], envp);
}

void	proc_piping(int i, int fds[2][2], char *argv, char *envp[])
{
	int	outfile;

	close(fds[i % 2][0]);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][1]);
	dup2(fds[!(i % 2)][0], STDIN_FILENO);
	outfile = open(argv, O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(outfile, STDOUT_FILENO);
	close(fds[!(i % 2)][0]);
	close(outfile);
	execute_cmd(argv, envp);
}

void	processing(int i, t_args args)
{
	pid_t	pid;
	int		fds[2][2];

	while (++i < args.argc - 1)
	{
		pipe(fds[i % 2]);
		pid = fork();
		if (pid == 0)
		{
			if (i == 2)
				proc_get_infile(i, fds, args.argv, args.envp);
			else if (i == args.argc - 2)
				proc_piping(i, fds, args.argv[i], args.envp);
			else
				proc_make_outfile(i, fds, args.argv, args.envp);
		}
		if (i != 2 && i != (args.argc - 2))
			close_a_pipe(fds[!(i % 2)]);
	}
	close_a_pipe(fds[0]);
	close_a_pipe(fds[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	int				i;
	const t_args	args = set_args(argc, argv, envp);

	if (argc < 5)
		return (0);
	i = 1;
	processing(i, args);
	return (0);
}
