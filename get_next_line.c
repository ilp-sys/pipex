/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 09:58:54 by jiwahn            #+#    #+#             */
/*   Updated: 2022/08/13 14:36:05 by jiwahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_nodd	*add_new_nodd(t_map *map, int key, char *value, int ret)
{
	t_nodd	*new_nodd;

	if (ret < 0)
		return (NULL);
	new_nodd = (t_nodd *)malloc(sizeof(t_nodd));
	if (!new_nodd)
		return (NULL);
	new_nodd->key = key;
	new_nodd->value = ft_strnoddup(value, ret);
	new_nodd->len = ret;
	new_nodd->next = NULL;
	if (map[key % MAP_SIZE].count == 0)
	{
		map[key % MAP_SIZE].count++;
		map[key % MAP_SIZE].head = new_nodd;
	}
	else
	{
		map[key % MAP_SIZE].count++;
		new_nodd->next = map[key % MAP_SIZE].head;
		map[key % MAP_SIZE].head = new_nodd;
	}
	return (map[key % MAP_SIZE].head);
}

t_nodd	*search(t_map *map, int key)
{
	t_nodd	*tmp;

	tmp = map[key % MAP_SIZE].head;
	while (tmp)
	{
		if (tmp->key == key)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int	re_read(t_nodd *nodd)
{
	int		ret;
	char	*buf_read;
	char	*buf_cpy;

	buf_read = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf_read)
		return (-1);
	ret = read(nodd->key, buf_read, BUFFER_SIZE);
	buf_cpy = (char *)malloc(nodd->len + ret);
	if (!buf_cpy)
	{
		free(buf_read);
		return (-1);
	}
	ft_memcpy(buf_cpy, nodd->value, nodd->len);
	ft_strnmcat(buf_cpy, buf_read, ret, nodd->len);
	nodd->len += ret;
	free(nodd->value);
	nodd->value = buf_cpy;
	free(buf_read);
	return (ret);
}

char	*get_ret_str(char *found, t_nodd *nodd, t_map *map)
{
	char	*ret_res;
	size_t	len;

	if (found == NULL)
	{
		len = nodd->len;
		ret_res = ft_strnoddup(nodd->value, len);
		nodd->len -= len;
		free_nodd(map, nodd->key);
	}
	else
	{
		(void)map;
		len = found + 1 - nodd->value;
		ret_res = ft_strnoddup(nodd->value, len);
		nodd->len -= len;
		ft_memcpy(nodd->value, found + 1, nodd->len);
	}
	return (ret_res);
}

char	*get_next_line(int fd)
{
	char			buf[BUFFER_SIZE];
	char			*found;
	size_t			ret;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (1)
	{
		found = ft_memchr(cur->value, '\n', cur->len);
		if (found != NULL)
			break ;
		ret = re_read(cur);
		if (ret == 0)
			break ;
		if (ret < 0)
			return (NULL);
	}
	return (get_ret_str(found, cur, map));
}
