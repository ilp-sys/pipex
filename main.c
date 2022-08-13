/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/13 21:20:48 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_get_infile(int i, int fds[2][2], char *argv[], char *envp[])
{
	int		infile;
	char	*tmp_file;

	if (i > 2)
	{
		tmp_file = get_stdin_heredoc(argv, envp);
		infile = open(tmp_file, O_RDONLY);
		unlink(tmp_file);
		free(tmp_file);
	}
	else
		infile = open(argv[1], O_RDONLY);
	close(fds[i % 2][0]);
	if (infile < 0)
		err_found_exit("file open failed");
	dup2_try_catch(infile, STDIN_FILENO);
	dup2_try_catch(fds[i % 2][1], STDOUT_FILENO);
	close(infile);
	close(fds[i % 2][1]);
	execute_cmd(argv[i], envp);
}

void	proc_make_outfile(int i, int fds[2][2], char *argv[], char *envp[])
{
	int	outfile;

	close(fds[i % 2][0]);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][1]);
	dup2_try_catch(fds[!(i % 2)][0], STDIN_FILENO);
	outfile = open(argv[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		err_found_exit("file open failed");
	dup2_try_catch(outfile, STDOUT_FILENO);
	close(fds[!(i % 2)][0]);
	close(outfile);
	execute_cmd(argv[i], envp);
}

void	proc_piping(int i, int fds[2][2], char *argv[], char *envp[])
{
	close(fds[i % 2][0]);
	close(fds[!(i % 2)][1]);
	dup2_try_catch(fds[i % 2][1], STDOUT_FILENO);
	dup2_try_catch(fds[!(i % 2)][0], STDIN_FILENO);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][0]);
	execute_cmd(argv[i], envp);
}

void	processing(int i, int here_doc, t_args args)
{
	pid_t	pid;
	int		fds[2][2];

	while (++i < args.argc - 1)
	{
		if (pipe(fds[i % 2]) == -1)
			err_found_exit("pipe failed");
		pid = fork();
		if (pid == 0)
		{
			if (i == (2 + (here_doc == 1)))
				proc_get_infile(i, fds, args.argv, args.envp);
			else if (i == args.argc - 2)
				proc_make_outfile(i, fds, args.argv, args.envp);
			else
				proc_piping(i, fds, args.argv, args.envp);
		}
		if (i != 2 && i != (args.argc - 2 && !here_doc))
			close_a_pipe(fds[!(i % 2)]);
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	close_a_pipe(fds[0]);
	close_a_pipe(fds[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	int				i;
	int				here_doc;
	const t_args	args = set_args(argc, argv, envp);

	if (argc < 5)
		err_found_exit("argument count not enough");
	i = 1;
	here_doc_check(&i, &here_doc, args);
	processing(i, here_doc, args);
	return (0);
}
