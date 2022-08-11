/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 13:35:36 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_here_doc(char *argv[])
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (1);
	return (0);
}

void	proc_get_infile(int i, int fds[2][2], char *argv[], char *envp[])
{
	close(fds[i % 2][0]);
	int infile = open(argv[1], O_RDONLY);
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
	close(fds[i % 2][0]);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][1]);
	dup2(fds[!(i % 2)][0], STDIN_FILENO);
	int outfile = open(argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	dup2(outfile , STDOUT_FILENO);
	close(fds[!(i % 2)][0]);
	close(outfile);
	execute_cmd(argv[i], envp);
}


// ./pipex infile.txt cmd1 cmd2 ... cmdn outfile
// ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn outfile
int main(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
		return ;

	int fds[2][2];

	int i = 1;
	const int	here_doc = check_here_doc(argv);

	if (here_doc)
		i += 1;
	while (++i < argc - 1)
	{
		pipe(fds[i % 2]); 

		pid_t pid = fork();
		if (pid == 0)
		{
			if (here_doc || i == 2)
				proc_get_infile(i, fds, argv, envp);
			else if (i == argc - 2)
				proc_piping(i, fds, argv[i], envp);
			else
				proc_make_outfile(i, fds, argv, envp);
		}
		fprintf(stderr, "pid %d was generated\n", pid);
		if (i != 2 && i != (argc - 2))
		{
			close(fds[!(i % 2)][0]);
			close(fds[!(i % 2)][1]);
		}
	}
	close(fds[0][0]);
	close(fds[0][1]);
	close(fds[1][0]);
	close(fds[1][1]);
	return (0);
}
