/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:59:26 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 00:44:13 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sys_err_exit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	close_utils(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

