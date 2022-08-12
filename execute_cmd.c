/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 18:23:42 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/12 19:53:43 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_abs_path(char *envp, char *cmd)
{
	char	*ret;

	ret = (char *)malloc(ft_strlen(envp) + 1 + ft_strlen(cmd) + 1);
	if (ret)
	{
		ft_strcpy(ret, envp);
		ft_strcat(ret, "/");
		ft_strcat(ret, cmd);
		ft_strcat(ret, "\0");
	}
	return (ret);
}

char	*get_pathname(char *envp[], char *cmd)
{
	int		i;
	char	*full_cmd;
	char	**path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		err_found_exit("PATH not exist");
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		full_cmd = get_abs_path(path[i], cmd);
		if (access(full_cmd, X_OK) == 0)
			break ;
		i++;
	}
	if (path[i] == NULL)
		err_found_exit("Command not found");
	free_split(path);
	return (full_cmd);
}

void	execute_cmd(char *argv, char **envp)
{
	char	**parsing;

	parsing = ft_split(argv, ' ');
	execve(get_pathname(envp, parsing[0]), parsing, envp);
	exit(1);
}
