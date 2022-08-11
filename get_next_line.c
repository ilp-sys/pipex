/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:27:45 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/11 13:48:09 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	re_read(int fd, t_str *buffer)
{
	size_t	ret;
	size_t	i;
	char	*tmp_read;
	char	*replace;
	char	*tmp_free;

	tmp_read = (char *)malloc(sizeof(char) * GNL_BUF_SIZE);
	if (!tmp_read)
		err_found_exit("Heap memory allocation failed!");
	ret = read(fd, tmp_read, GNL_BUF_SIZE);
	if (ret < 0)
		err_found_exit("System call read failed!");
	replace = (char *)malloc(buffer->len + ret);
	if (!replace)
		err_found_exit("Heap memory allocation failed!");
	ft_strncpy(replace, buffer->str, buffer->len);
	ft_strncat(replace, tmp_read, ret);
	tmp_free = buffer->str;
	buffer->len += ret;
	buffer->str = replace;
	free(tmp_free);
	return (ret);
}

static char	*make_ret_str(t_str *buffer, size_t ret, char *new_line_pos)
{
	size_t	ret_len;
	char	*ret_str;
	char	*replace;
	char	*tmp;

	if (ret == 0)
		ret_len = buffer->len;
	else
		ret_len = new_line_pos + 1 - buffer->str;
	ret_str = (char *)malloc(sizeof(char) * ret_len + 1);
	if (!ret_str)
		err_found_exit("Heap memory allocation failed!");
	ft_strncpy(ret_str, buffer->str, ret_len);
	ret_str[ret_len] = '\0';
	buffer->len -= ret_len;
	if (ret == 0)
		replace = NULL;
	else
	{
		replace = (char *)malloc(sizeof(char) * buffer->len);
		if (!replace)
			err_found_exit("Heap memory allocation failed!")
		ft_strncat(replace, new_line_pos + 1, buffer->len);
	}
	tmp = buffer->str;
	buffer->str = replace;
	free(tmp);
	return (ret_str);
}

char	*get_next_line(int fd)
{
	static t_str	buffer;
	char			*new_line_pos;
	size_t			ret;

	if (buffer.str == NULL)
	{
		buffer.str = (char *)malloc(sizeof(char) * GNL_BUF_SIZE);
		if (!buffer.str)
			err_found_exit("Heap memory allocation failed!");
	}
	while (1)
	{
		new_line_pos = ft_memchr(buffer.str, buffer.len);
		if (new_line_pos != NULL)
			break ;
		ret = re_read(int fd, &buffer);
		if (ret < 0) //TODO - redundancy here
			err_found_exit("System call read failed!");
		if (ret == 0)
			break ;
	}
	return (make_ret_str());
}
