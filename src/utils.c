/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/21 11:09:27 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/21 11:09:28 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_string		*get_time(time_t m_time)
{
	time_t			now;
	time_t const	timeout = 6 * 30 * 24 * 60 * 60;
	char			**split;
	int				i;
	t_string		*tmp;

	tmp = ft_stringnew();
	split = ft_strsplit(ctime(&m_time), ' ');
	time(&now);
	ft_stringadd(tmp, split[2]);
	ft_stringaddc(tmp, ' ');
	ft_strlower(split[1]);
	ft_stringadd(tmp, split[1]);
	ft_stringaddc(tmp, ' ');
	split[3][5] = '\0';
	if (m_time <= now - timeout || m_time >= now + timeout)
		ft_stringadd(tmp, split[4]);
	else
		ft_stringadd(tmp, split[3]);
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	return (tmp);
}

void			*filenew(char *name, char *path, DIR *dir)
{
	t_file			*file;
	struct stat		*stats;

	stats = MAL1(struct stat);
	file = MAL1(t_file);
	file->path = ft_stringnew();
	ft_stringadd(file->path, path);
	while (file->path->length > 1 &&
		file->path->content[file->path->length - 1] == '/')
		ft_stringrem(file->path, file->path->length - 1, 1);
	if (file->path->length > 0)
		ft_stringaddc(file->path, '/');
	ft_stringadd(file->path, name);
	file->dir = dir;
	if (stat(file->path->content, stats) < 0)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_stringputfd(file->path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_stringkil(file->path);
		free(file);
		return (NULL);
	}
	file->stats = stats;
	return ((void*)file);
}
