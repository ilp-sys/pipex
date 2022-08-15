/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:21:19 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/15 21:00:28 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_check(int *i, int *here_doc, t_args args)
{
	if (ft_strcmp(args.argv[1], "here_doc") == 0)
	{
		(*i)++;
		*here_doc = 1;
	}
	else
		*here_doc = 0;
}

void	stdin_get_next_line(int fd, char *limiter)
{
	int		ret;
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)) && \
				ft_strlen(limiter) == ft_strlen(line) - 1)
		{
			free(line);
			break ;
		}
		ret = write(fd, line, ft_strlen(line));
		if (ret < 0)
			err_found_exit();
		free(line);
	}
}

char	*get_stdin_heredoc(char *argv[], char *envp[])
{
	int		infile_fd;
	char	*abs_path;

	while (*envp)
		if (ft_strncmp(*(envp++), "TMPDIR=", 7) == 0)
			break ;
	if (*envp == NULL)
		err_found_exit();
	abs_path = ft_strjoin(*envp + 7, TMP_FILE_NAME);
	if (abs_path == NULL)
		err_found_exit();
	if (access(abs_path, F_OK) != -1)
		err_found_exit();
	infile_fd = open(abs_path, O_WRONLY | O_CREAT, 0644);
	stdin_get_next_line(infile_fd, argv[2]);
	close(infile_fd);
	return (abs_path);
}
