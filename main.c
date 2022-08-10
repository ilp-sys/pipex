/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 05:19:59 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_abs_path(char *envp, char *cmd)
{
    char    *ret;

    ret = (char *)malloc(ft_strlen(envp) +  + 1 + ft_strlen(cmd) + 1);
    if (ret)
    {
        ft_strcpy(ret, envp);
        ft_strcat(ret, "/");
        ft_strcat(ret, cmd); //cat null char at the end
    }
    return (ret);
}


char	*get_pathname(char *envp[], char *cmd)
{
	int		i;
	char	*full_cmd;

	i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		sys_err_exit("PATH not exist");
	char	**path = ft_split(envp[i] + 5, ':');
	while (*path)
	{
		full_cmd = get_abs_path(*path, cmd);
		if (access(full_cmd, X_OK) == 0)
			break;
		(*path)++;
	}
	if (*path == NULL)
		sys_err_exit("Command not found");
	fprintf(stderr, "%s\n", full_cmd);
	return (full_cmd);
}

int main(int argc, char *argv[], char *envp[])
{
	// ./piepx infile.txt cmd1 cmd2 ... cmdn outfile
	if (argc > 4)
	{
		int fds[2][2];

		int i = 1;
		while (++i < argc - 1)
		{
			pipe(fds[i % 2]); //starting from odd number

			pid_t pid = fork();
			if (pid == 0)
			{
				if (i == 2)
				{
					close(fds[i % 2][0]);
					int infile = open(argv[1], O_RDONLY);
					dup2(infile, STDIN_FILENO);
					dup2(fds[i % 2][1], STDOUT_FILENO);
					close(infile);
					close(fds[i % 2][1]);
					char **parsing = ft_split(argv[i], ' ');
					execve(get_abs_path(envp, parsing[0]), parsing, envp);
					exit(1);
				}
				else if (i == argc - 2)
				{
					close();
					close();
				}
				else
				{
					close(fd[i % 2][0]);
					close(fd[!(i % 2)][1]);
					dup2(fd[i % 2][1], STDOUT_FILENO);
					dup2(fd[!(i % 2)][0], STDIN_FILENO);
					close(fd[i % 2][1]);
					close(fd[!(i % 2)][0]);
					char **parsing = ft_split(argv[i], ' ');
					execve(get_abs_path(envp, parsing[0]), parsing, envp);
					exit(1);
				}
			}
			//TODO
			//close fds if available
		}
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[1][1]);
	}
	return (0);
}
