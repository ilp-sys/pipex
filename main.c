/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 11:43:06 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/10 23:07:47 by jiwahn           ###   ########.fr       */
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
		int i = 1;
		int fd[2];
		pipe(fd);

		int tmp = open(argv[i], O_RDONLY);
		dup2(tmp, STDIN_FILENO);
		close(tmp);
		while (i++ < argc - 1)
		{
			pid_t pid = fork();
			if (pid == (pid_t)0)
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				char **parsing = ft_split(argv[i], ' ');
				execve(get_pathname(envp, parsing[0]), parsing, envp);
			}
		}
		int tmp2 = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC);
		dup2(tmp2, STDOUT_FILENO);
		close(tmp2);

		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}
