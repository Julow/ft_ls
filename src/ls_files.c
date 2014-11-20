/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 19:21:43 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/19 19:21:43 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_special_mode(mode_t ifmt)
{
	if (ifmt == S_IFDIR || ifmt == S_IFSOCK)
		return ((ifmt == S_IFDIR) ? 'd' : 's');
	if (ifmt == S_IFCHR || ifmt == S_IFIFO)
		return ((ifmt == S_IFCHR) ? 'c' : 'p');
	if (ifmt == S_IFLNK || ifmt == S_IFBLK)
		return ((ifmt == S_IFLNK) ? 'l' : 'b');
	return ('-');
}

static void		get_modes(t_string *output, mode_t mode)
{
	ft_stringaddc(output, get_special_mode(mode & S_IFMT));
	ft_stringaddc(output, (mode & (1 << (9 - 1))) ? 'r' : '-');
	ft_stringaddc(output, (mode & (1 << (9 - 2))) ? 'w' : '-');
	if (mode & (1 << (9 - 3)))
		ft_stringaddc(output, (mode & (1 << (12 - 1))) ? 's' : 'x');
	else
		ft_stringaddc(output, (mode & (1 << (12 - 1))) ? 'S' : '-');
	ft_stringaddc(output, (mode & (1 << (9 - 4))) ? 'r' : '-');
	ft_stringaddc(output, (mode & (1 << (9 - 5))) ? 'w' : '-');
	if (mode & (1 << (9 - 3)))
		ft_stringaddc(output, (mode & (1 << (12 - 2))) ? 's' : 'x');
	else
		ft_stringaddc(output, (mode & (1 << (12 - 1))) ? 'S' : '-');
	ft_stringaddc(output, (mode & (1 << (9 - 7))) ? 'r' : '-');
	ft_stringaddc(output, (mode & (1 << (9 - 8))) ? 'w' : '-');
	if (mode & (1 << (9 - 3)))
		ft_stringaddc(output, (mode & (1 << (12 - 3))) ? 't' : 'x');
	else
		ft_stringaddc(output, (mode & (1 << (12 - 1))) ? 'T' : '-');
}

static void		ls_file(t_string *out, char *name, t_file *file, t_args *args)
{
	if (FLAG(FLAG_L))
	{
		get_modes(out, file->stats->st_mode);
		ft_stringadd(out, " 0 ");
		ft_stringadd(out, getpwuid(file->stats->st_uid)->pw_name);
		ft_stringaddc(out, ' ');
		ft_stringadd(out, getgrgid(file->stats->st_gid)->gr_name);
		ft_stringaddc(out, ' ');
	}
	ft_stringadd(out, name);
	if (FLAG(FLAG_1))
		ft_stringaddc(out, '\n');
	else
		ft_stringadd(out, "		");
}

void			ls_files(t_string *output, t_array *files, t_args *args)
{
	int				i;
	char			*tmp;

	if (FLAG(FLAG_SORT))
		filesort(files, args);
	else if (!FLAG(FLAG_F))
		ft_mapsort(files);
	if (FLAG(FLAG_R))
		ft_arrayrev(files);
	i = -1;
	while (++i < files->length)
	{
		tmp = ((t_map*)files->data[i])->key->content;
		if (!FLAG(FLAG_A) && (ft_strequ(tmp, ".") || ft_strequ(tmp, "..")))
			continue;
		else if (!FLAG(FLAG_AA) && (tmp[0] == '.'))
			continue;
		ls_file(output, tmp, (t_file*)((t_map*)files->data[i])->value, args);
	}
}
