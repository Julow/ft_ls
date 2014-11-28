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
	ft_stringadd(tmp, split[1]);
	ft_stringaddcn(tmp, ' ', (ft_strlen(split[2]) == 1) ? 2 : 1);
	ft_stringadd(tmp, split[2]);
	ft_stringaddc(tmp, ' ');
	if (m_time <= now - timeout || m_time >= now + timeout)
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