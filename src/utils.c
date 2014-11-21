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

void			get_time(t_string *out, time_t m_time)
{
	char			*tmp;
	time_t			now;
	time_t const	timeout = 6 * 30 * 24 * 60 * 60;
	int				i;

	tmp = ctime(&m_time);
	time(&now);
	i = 16;
	if (m_time <= now - timeout || m_time >= now + timeout)
	{
		while (tmp[i - 1] != ' ')
		{
			tmp[i] = tmp[i + 4];
			i++;
		}
	}
	tmp[i] = '\0';
	ft_stringadd(out, tmp + 4);
}

void			*filenew(char *name, char *path, DIR *dir)
{
	t_file			*file;
	struct stat		*stats;

	stats = MAL1(struct stat);
	file = MAL1(t_file);
	file->path = ft_stringnew();
	ft_stringadd(file->path, path);
	while (file->path->content[file->path->length - 1] == '/')
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
		ft_stringkil(&(file->path));
		free(file);
		return (NULL);
	}
	file->stats = stats;
	return ((void*)file);
}

t_bool			ft_stringaddcn(t_string *str, char c, int n)
{
	ft_stringext(str, n);
	while (--n >= 0)
	{
		if (!ft_stringaddc(str, c))
			return (FALSE);
	}
	return (TRUE);
}