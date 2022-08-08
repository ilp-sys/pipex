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

char	**get_args(char **parsing)
{
	int			i;
	const char	*deli = ":'\"";

	i = 0;
	while (parsing[i])
	{
		parsing[i] = ft_strtrim(parsing[i], deli);
		i++;
	}
	return (parsing);
}

char	*get_abs_path(char *argp, char *cmd)
{
	char	*ret;

	ret = (char *)malloc(ft_strlen(argp) +  + 1 + ft_strlen(cmd) + 1);
	if (ret)
	{
		ft_strcpy(ret, argp);
		ft_strcat(ret, "/");
		ft_strcat(ret, cmd);
	}
	return (ret);
}

char	*get_pathname(char *argp[], char *cmd)
{
	while (*argp)
	{
		if (ft_strncmp(*argp, "PATH=", 5) == 0)
			break;
		(*argp)++;
	}
	if (*argp == NULL)
	{
		perror("PATH not exist\n");
		exit(0);
	}
	return (get_abs_path(*argp, cmd));
}

int	main(int argc, char *argv[], char *argp[])
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	if (argc == 5)
	{
		if (pipe(fd))
		{
			perror("Pipe generate failed\n");
			exit(0);
		}

		pid = fork();
		if (pid == (pid_t)0)
		{
			dup2(fd[1], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			char	**parsing = ft_split(argv[2], ' ');
			execve(get_pathname(argp, parsing[0]), get_args(parsing), NULL);
		}

		pid2 = fork();
		if (pid2 == (pid_t)0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
			char	**parsing2 = ft_split(argv[3], ' ');
			execve(get_pathname(argp, parsing2[0]), get_args(parsing2), NULL);
		}

		close(fd[0]);
		close(fd[1]);

		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}

	return 0;
}
