/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:41:36 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/09 19:11:26 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>

# include "libft/libft.h"

# define GNL_BUF_SIZE 1024 

typedef struct s_str
{
	size_t	len;
	char	*str;
}t_str;

char	*get_next_line(int fd);

void	sys_err_exit(char *msg);

#endif
