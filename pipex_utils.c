/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:59:26 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 14:12:01 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	err_found_exit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void	sys_err_exit(int (*func)())
{

}
