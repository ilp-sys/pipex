/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:21:53 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 13:45:30 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_abs_path(char *envp, char *cmd)
{
    char    *ret;

    ret = (char *)malloc(ft_strlen(envp) +  + 1 + ft_strlen(cmd) + 1);
    if (ret)
    {
        ft_strcpy(ret, envp);
        ft_strcat(ret, "/");
        ft_strcat(ret, cmd); //TODO - cat null char at the end
    }
    return (ret);
}

char    *get_pathname(char *envp[], char *cmd)
{
    int     i;
    char    *full_cmd;

    i = 0;
    while(ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (envp[i] == NULL)
        err_found_exit("PATH not exist");
    char    **path = ft_split(envp[i] + 5, ':');
    while (*path)
    {
        full_cmd = get_abs_path(*path, cmd);
        if (access(full_cmd, X_OK) == 0)
            break;
        (*path)++;
    }
    if (*path == NULL)
        err_found_exit("Command not found");
    fprintf(stderr, "%s\n", full_cmd);
    return (full_cmd);
}

void	execute_cmd(char *argv, char **envp)
{
    char    **parsing;

    parsing = ft_split(argv, ' ');
    execve(get_pathname(envp, parsing[0]), parsing, envp);
    //TODO - freeing parsed cmd iteratively
    exit(1);
}
