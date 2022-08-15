/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:12:38 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/15 20:59:51 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strnmcat(char *s1, const char *s2, size_t n, size_t m)
{
	char	*ret;

	ret = s1;
	while (m-- && *s1)
		s1++;
	while (n-- && *s2)
		*s1++ = *s2++;
	return (ret);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;

	if (n == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * n + 1);
	if (!ret)
		return (NULL);
	ret = ft_memcpy(ret, s1, n);
	ret[n] = '\0';
	return (ret);
}

static int	re_read(int fd, t_str *str)
{
	int		ret;
	char	*buf_read;
	char	*buf_cpy;

	buf_read = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf_read)
		return (-1);
	ret = read(fd, buf_read, BUFFER_SIZE);
	buf_cpy = (char *)malloc(str->len + ret);
	if (!buf_cpy)
	{
		free(buf_read);
		return (-1);
	}
	ft_memcpy(buf_cpy, str->str, str->len);
	ft_strnmcat(buf_cpy, buf_read, ret, str->len);
	str->len += ret;
	free(str->str);
	str->str = buf_cpy;
	free(buf_read);
	return (ret);
}

static char	*get_ret_str(char *found, t_str *str)
{
	char	*ret_res;
	size_t	len;

	if (found == NULL)
	{
		len = str->len;
		ret_res = ft_strndup(str->str, len);
		str->len -= len;
	}
	else
	{
		len = found + 1 - str->str;
		ret_res = ft_strndup(str->str, len);
		str->len -= len;
		ft_memcpy(str->str, found + 1, str->len);
	}
	return (ret_res);
}

char	*get_next_line(int fd)
{
	char			*found;
	size_t			ret;
	static t_str	str;

	if (fd < 0)
		err_found_exit();
	while (1)
	{
		found = ft_memchr(str.str, '\n', str.len);
		if (found != NULL)
			break ;
		ret = re_read(fd, &str);
		if (ret == 0)
			break ;
		if (ret < 0)
			err_found_exit();
	}
	return (get_ret_str(found, &str));
}
