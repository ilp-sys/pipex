/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:40:55 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/05 20:20:43 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int argc, char *argv[], char *argp[])
{
	int	fd1;
	int	fd2;

	if (argc > 4)
	{
		fd1 = check_heredoc(argv[1]); //error handling (negative fd)
		while ()
		{

		}
	}
	return 0;
}
