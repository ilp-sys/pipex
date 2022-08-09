/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:40:55 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/09 14:40:40 by jiwahn           ###   ########.fr       */
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
	int		i;
	char	*full_cmd;

	i = 0;
	while (argp[i])
	{
		if (ft_strncmp(argp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	if (argp[i] == NULL)
	{
		perror("PATH not exist\n");
		exit(0);
	}
	char	**path = ft_split(argp[i] + 5, ':');
	while (*path)
	{
		full_cmd = get_abs_path(*path, cmd);
		if (access(full_cmd, X_OK) == 0)
			break;
		//free(full_cmd);
		(*path)++;
	}
	if (*path == NULL)
	{
		perror("PATH not exist\n");
		exit(0);
	}
	//fprintf(stderr, "Executable bin path:%s\n", full_cmd);
	return (full_cmd);
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
			perror("Pipe creation failed\n");
			exit(0);
		}

		pid = fork();
		if (pid == (pid_t)0)
		{
			int tmp_fd = open(argv[1], O_RDONLY);
			dup2(tmp_fd, STDIN_FILENO);
//			char *buffer = (char *)malloc(sizeof(char) * 100);
//			int ret = read(0, buffer, 100);
//			write(1, buffer, ret);
			dup2(fd[1], STDOUT_FILENO);
			close(tmp_fd);
			close(fd[0]);
			close(fd[1]);
			char	**parsing = ft_split(argv[2], ' ');
			execve(get_pathname(argp, parsing[0]), get_args(parsing), argp);
			exit(0);
		}

		pid2 = fork();
		if (pid2 == (pid_t)0)
		{
			dup2(fd[0], STDIN_FILENO);
//			char *buffer = (char *)malloc(sizeof(char) * 100);
//			int ret = read(0, buffer, 100);
//			write(1, buffer, ret);
			int tmp_fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
			dup2(tmp_fd2, STDOUT_FILENO);
			close(tmp_fd2);
			close(fd[1]);
			close(fd[0]);
			char	**parsing2 = ft_split(argv[3], ' ');
			execve(get_pathname(argp, parsing2[0]), get_args(parsing2), argp);
			exit(0);
		}

		close(fd[0]);
		close(fd[1]);

		waitpid(pid, NULL, 0);
		waitpid(pid2, NULL, 0);
	}

	return 0;
}
