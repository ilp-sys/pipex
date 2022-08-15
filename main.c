/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/15 21:01:06 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_get_infile(int here_doc, int i, int fds[2][2], t_args args)
{
	int		infile;
	char	*tmp_file;

	if (here_doc)
	{
		tmp_file = get_stdin_heredoc(args.argv, args.envp);
		infile = open(tmp_file, O_RDONLY);
		unlink(tmp_file);
		free(tmp_file);
	}
	else
		infile = open(args.argv[1], O_RDONLY);
	close(fds[i % 2][0]);
	if (infile < 0)
		err_found_exit();
	dup2_try_catch(infile, STDIN_FILENO);
	dup2_try_catch(fds[i % 2][1], STDOUT_FILENO);
	close(infile);
	close(fds[i % 2][1]);
	execute_cmd(args.argv[i], args.envp);
}

void	proc_make_outfile(int here_doc, int i, int fds[2][2], t_args args)
{
	int	outfile;

	close(fds[i % 2][0]);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][1]);
	dup2_try_catch(fds[!(i % 2)][0], STDIN_FILENO);
	if (here_doc)
		outfile = open(args.argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile = open(args.argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		err_found_exit();
	dup2_try_catch(outfile, STDOUT_FILENO);
	close(fds[!(i % 2)][0]);
	close(outfile);
	execute_cmd(args.argv[i], args.envp);
}

void	proc_piping(int i, int fds[2][2], t_args args)
{
	close(fds[i % 2][0]);
	close(fds[!(i % 2)][1]);
	dup2_try_catch(fds[i % 2][1], STDOUT_FILENO);
	dup2_try_catch(fds[!(i % 2)][0], STDIN_FILENO);
	close(fds[i % 2][1]);
	close(fds[!(i % 2)][0]);
	execute_cmd(args.argv[i], args.envp);
}

void	processing(int here_doc, int i, t_args args)
{
	pid_t	pid;
	int		fds[2][2];

	while (++i < args.argc - 1)
	{
		if (pipe(fds[i % 2]) == -1)
			err_found_exit();
		pid = fork();
		if (pid == 0)
		{
			if (i == (2 + (here_doc == 1)))
				proc_get_infile(here_doc, i, fds, args);
			else if (i == args.argc - 2)
				proc_make_outfile(here_doc, i, fds, args);
			else
				proc_piping(i, fds, args);
		}
		if (i != 2 && i != (args.argc - 2 && !here_doc))
			close_a_pipe(fds[!(i % 2)]);
	}
	close_a_pipe(fds[0]);
	close_a_pipe(fds[1]);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

int	main(int argc, char *argv[], char *envp[])
{
	int				i;
	int				here_doc;
	const t_args	args = set_args(argc, argv, envp);

	if (argc < 5)
		err_found_exit();
	i = 1;
	here_doc_check(&i, &here_doc, args);
	processing(here_doc, i, args);
	return (0);
}
