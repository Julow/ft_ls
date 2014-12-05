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
	if (FLAG(FLAG_FF) || FLAG(FLAG_P))
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

t_bool			is_visible(t_string *name, t_args *args)
{
	return (((FLAG(FLAG_AA) || !(name->content[0] == '.' && name->content[1] != '/'))
		&& (FLAG(FLAG_A) || (!ft_strequ(name->content, ".") &&
			!ft_strequ(name->content, "..")))) ? TRUE : FALSE);
}

t_string		*get_time(time_t m_time)
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
	if (m_time <= now - MONTH(6) || m_time > now)
	{
		ft_stringaddc(tmp, ' ');
		ft_stringaddl(tmp, split[4], 4);
	}
	else
		ft_stringaddl(tmp, split[3], 5);
	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	return (tmp);
}
/*
t_bool			hide_file(t_array *files, int *i, t_args *args)
{
	t_file			*tmp;

	tmp = (t_file*)files->data[*i];
	if ((!FLAG(FLAG_AA) && (tmp->name->content[0] == '.')) || (!FLAG(FLAG_A)
		&& (ft_strequ(tmp->name->content, ".") ||
			ft_strequ(tmp->name->content, ".."))))
	{
		kill_file(files->data[*i]);
		ft_arrayrem(files, (*i)--);
		return (TRUE);
	}
	return (FALSE);
}
*/
