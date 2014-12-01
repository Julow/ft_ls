/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 11:22:16 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/28 11:22:17 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_string		*get_pwuid(uid_t id, t_args *args)
{
	struct passwd	*passwd;

	passwd = getpwuid(id);
	if (FLAG(FLAG_G))
		return (ft_stringnews(""));
	if (passwd != NULL && passwd->pw_name != NULL)
		return (ft_stringnews(passwd->pw_name));
	return (ft_stringi(id));
}

t_string		*get_grgid(uid_t id, t_args *args)
{
	struct group	*grp;

	grp = getgrgid(id);
	if (FLAG(FLAG_O))
		return (ft_stringnews(""));
	if (grp != NULL && grp->gr_name != NULL)
		return (ft_stringnews(grp->gr_name));
	return (ft_stringi(id));
}

char			get_special_mode(mode_t ifmt)
{
	if (ifmt == S_IFDIR || ifmt == S_IFSOCK)
		return ((ifmt == S_IFDIR) ? 'd' : 's');
	if (ifmt == S_IFCHR || ifmt == S_IFIFO)
		return ((ifmt == S_IFCHR) ? 'c' : 'p');
	if (ifmt == S_IFLNK || ifmt == S_IFBLK)
		return ((ifmt == S_IFLNK) ? 'l' : 'b');
	return ('-');
}

t_string		*get_major(t_stat *s)
{
	t_string		*str;

	str = ft_stringnew();
	if ((s->st_mode & S_IFMT) == S_IFCHR || (s->st_mode & S_IFMT) == S_IFBLK)
	{
		ft_stringaddi(str, MAJOR(s->st_rdev));
		ft_stringaddc(str, ',');
	}
	return (str);
}

t_string		*get_minor(t_stat *s)
{
	t_string		*str;

	str = ft_stringnew();
	if ((s->st_mode & S_IFMT) == S_IFCHR || (s->st_mode & S_IFMT) == S_IFBLK)
		ft_stringaddi(str, MINOR(s->st_rdev));
	else
		ft_stringaddi(str, s->st_size);
	return (str);
}
