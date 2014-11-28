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

t_string		*get_name(t_file *file, char *name, t_args *args)
{
	t_string		*str;
	char			tmp[1024];
	int				length;
	int const		mode = file->stats->st_mode & S_IFMT;

	str = ft_stringnew();
	ft_stringadd(str, name);
	if (FLAG(FLAG_FF) && (mode == S_IFDIR || mode == S_IFLNK))
		ft_stringaddc(str, (mode == S_IFDIR) ? '/' : '@');
	else if (FLAG(FLAG_FF) && (mode == S_IFIFO || mode == S_IFSOCK))
		ft_stringaddc(str, (mode == S_IFIFO) ? '|' : '=');
	else if (FLAG(FLAG_FF) && mode == S_IFWHT)
		ft_stringaddc(str, '%');
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
