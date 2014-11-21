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

static void		ls_file1(t_string *out, t_string *n, t_file *f, t_args *args)
{
	if (FLAG(FLAG_L))
	{
		get_modes(out, f->stats->st_mode);
		ft_stringadd(out, "  ");
		ft_stringaddi(out, f->stats->st_nlink);
		ft_stringaddc(out, ' ');
		ft_stringadd(out, getpwuid(f->stats->st_uid)->pw_name);
		ft_stringadd(out, "  ");
		ft_stringadd(out, getgrgid(f->stats->st_gid)->gr_name);
		ft_stringadd(out, "  ");
		ft_stringaddi(out, f->stats->st_size);
		ft_stringaddc(out, ' ');
		get_time(out, f->stats->st_mtimespec.tv_sec);
		ft_stringaddc(out, ' ');
	}
	ft_stringaddl(out, n->content, n->length);
	ft_stringaddc(out, '\n');
}

static void		ls_column(t_string *out, t_array *files, int len)
{
	int				i;
	int				j;
	struct ttysize	ts;
	int				columns;
	int				lines;
	t_map			*tmp;

	ioctl(0, TIOCGSIZE, &ts);
	i = -1;
	columns = (ts.ts_cols > len && len > 0) ? ts.ts_cols / len : 1;
	lines = files->length / columns + ((files->length % columns > 0) ? 1 : 0);
	while (++i < lines)
	{
		j = -1;
		while (++j < columns && j * lines + i < files->length)
		{
			tmp = (t_map*)files->data[j * lines + i];
			ft_stringaddl(out, tmp->key->content, tmp->key->length);
			if (j + 1 < columns)
				ft_stringaddcn(out, ' ', len - tmp->key->length);
		}
		ft_stringaddc(out, '\n');
	}
}

void			ls_files(t_string *out, t_array *files, t_args *args)
{
	int				i;
	int				max_len;
	t_string		*tmp;

	if (FLAG(FLAG_SORT))
		filesort(files, args);
	else if (!FLAG(FLAG_F))
		ft_mapsort(files);
	if (FLAG(FLAG_R))
		ft_arrayrev(files);
	i = -1;
	max_len = 8;
	while (++i < files->length)
	{
		tmp = ((t_map*)files->data[i])->key;
		if (FLAG(FLAG_1))
			ls_file1(out, tmp, (t_file*)((t_map*)files->data[i])->value, args);
		while (tmp->length >= max_len)
			max_len += 8;
	}
	if (!FLAG(FLAG_1))
		ls_column(out, files, max_len);
}