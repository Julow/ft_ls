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
#include <stdlib.h>

t_string		*ft_stringi(int n)
{
	t_string		*tmp;

	tmp = ft_stringnew();
	ft_stringaddi(tmp, n);
	return (tmp);
}

t_string		*get_name(t_file *file, char *name, t_args *args)
{
	t_string		*str;
	char			tmp[1024];
	int				length;
	int const		mode = file->stats->st_mode & S_IFMT;

	str = ft_stringnew();
	ft_stringadd(str, name);
	if ((FLAG(FLAG_FF) || FLAG(FLAG_P)) && mode == S_IFDIR)
		ft_stringaddc(str, '/');
	else if (FLAG(FLAG_FF) && (mode == S_IFIFO || mode == S_IFSOCK))
		ft_stringaddc(str, (mode == S_IFIFO) ? '|' : '=');
	else if (FLAG(FLAG_FF) && (mode == S_IFWHT || mode == S_IFLNK))
		ft_stringaddc(str, (mode == S_IFWHT) ? '%' : '@');
	else if (FLAG(FLAG_FF) && (file->stats->st_mode & S_IXUSR ||
		file->stats->st_mode & S_IXGRP || file->stats->st_mode & S_IXOTH))
		ft_stringaddc(str, '*');
	if (FLAG(FLAG_L) && mode == S_IFLNK)
	{
		ft_stringadd(str, " -> ");
		length = readlink(file->path->content, tmp, 1024);
		ft_stringaddl(str, tmp, length);
	}
	return (str);
}

t_bool			is_visible(char *name, t_args *args)
{
	return (((FLAG(FLAG_AA) || !(name[0] == '.' && name[1] != '/'))
		&& (FLAG(FLAG_A) || (!ft_strequ(name, ".") &&
			!ft_strequ(name, "..")))) ? TRUE : FALSE);
}

static t_string	*format_time(time_t m_time, t_args *args)
{
	time_t			now;
	char			**split;
	int				i;
	t_string		*tmp;

	tmp = ft_stringnew();
	split = ft_strsplit(ctime(&m_time), ' ');
	time(&now);
	ft_stringadd(tmp, split[1]);
	ft_stringaddcn(tmp, ' ', (ft_strlen(split[2]) == 1) ? 2 : 1);
	ft_stringadd(tmp, split[2]);
	ft_stringaddc(tmp, ' ');
	if (m_time > now - MONTH(6) && m_time <= now)
		ft_stringaddl(tmp, split[3], (FLAG(FLAG_TT)) ? 8 : 5);
	if (m_time <= now - MONTH(6) || m_time > now || FLAG(FLAG_TT))
	{
		ft_stringaddc(tmp, ' ');
		ft_stringaddl(tmp, split[4], 4);
	}
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	return (tmp);
}

t_string		*get_time(t_file *file, t_args *args)
{
	if (FLAG(FLAG_U))
		return (format_time(file->stats->st_atimespec.tv_sec, args));
	if (FLAG(FLAG_UU))
		return (format_time(file->stats->st_birthtimespec.tv_sec, args));
	if (FLAG(FLAG_C))
		return (format_time(file->stats->st_ctimespec.tv_sec, args));
	return (format_time(file->stats->st_mtimespec.tv_sec, args));
}
