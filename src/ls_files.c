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

static t_string	*get_modes(char *n, mode_t mode)
{
	t_string		*tmp;

	tmp = ft_stringnew();
	ft_stringaddc(tmp, get_special_mode(mode & S_IFMT));
	ft_stringaddc(tmp, (mode & (1 << (9 - 1))) ? 'r' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 2))) ? 'w' : '-');
	if (mode & (1 << (9 - 3)))
		ft_stringaddc(tmp, (mode & (1 << (12 - 1))) ? 's' : 'x');
	else
		ft_stringaddc(tmp, (mode & (1 << (12 - 1))) ? 'S' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 4))) ? 'r' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 5))) ? 'w' : '-');
	if (mode & (1 << (9 - 6)))
		ft_stringaddc(tmp, (mode & (1 << (12 - 2))) ? 's' : 'x');
	else
		ft_stringaddc(tmp, (mode & (1 << (12 - 2))) ? 'S' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 7))) ? 'r' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 8))) ? 'w' : '-');
	if (mode & (1 << (9 - 9)))
		ft_stringaddc(tmp, (mode & (1 << (12 - 3))) ? 't' : 'x');
	else
		ft_stringaddc(tmp, (mode & (1 << (12 - 3))) ? 'T' : '-');
	ft_stringaddc(tmp, (listxattr(n, NULL, 0, XATTR_NOFOLLOW) > 0) ? '@' : ' ');
	return (tmp);
}

static void		ls_file1(t_array *table, t_file *file, t_args *args)
{
	if (FLAG(FLAG_L))
	{
		col_add((t_col*)table->data[0], get_modes(file->path->content,
			file->stats->st_mode));
		col_add((t_col*)table->data[1], ft_stringi(file->stats->st_nlink));
		((t_col*)table->data[1])->left = FALSE;
		col_add((t_col*)table->data[2], ft_strings((FLAG(FLAG_G)) ? "" :
			getpwuid(file->stats->st_uid)->pw_name));
		((t_col*)table->data[2])->left = 2;
		col_add((t_col*)table->data[3], ft_strings((FLAG(FLAG_O)) ? "" :
			getgrgid(file->stats->st_gid)->gr_name));
		((t_col*)table->data[3])->left = 2;
		col_add((t_col*)table->data[4], get_major(file->stats));
		((t_col*)table->data[4])->left = (FLAG(FLAG_O) && FLAG(FLAG_G)) ?
			-3 : -1;
		col_add((t_col*)table->data[5], get_minor(file->stats));
		((t_col*)table->data[5])->left = FALSE;
		col_add((t_col*)table->data[6],
			get_time(file->stats->st_mtimespec.tv_sec));
	}
	col_add((t_col*)table->data[7], ft_stringdup(file->name));
}

static void		ls_column(t_string *out, t_array *files, int len, t_file *tmp)
{
	int				i;
	int				j;
	struct ttysize	ts;
	int				columns;
	int				lines;

	ioctl(1, TIOCGSIZE, &ts);
	i = -1;
	columns = (ts.ts_cols > len && len > 0) ? ts.ts_cols / len : 1;
	lines = files->length / columns + ((files->length % columns > 0) ? 1 : 0);
	while (++i < lines)
	{
		j = -1;
		while (++j < columns && j * lines + i < files->length)
		{
			tmp = (t_file*)files->data[j * lines + i];
			ft_stringaddl(out, tmp->name->content, tmp->name->length);
			if (j + 1 < columns)
				ft_stringaddcn(out, ' ', len - tmp->name->length);
		}
		ft_stringaddc(out, '\n');
		ft_stringput(out);
		out->length = 0;
	}
}

void			kill_file(void *file)
{
	t_file			*tmp;

	tmp = (t_file*)file;
	ft_stringkil(tmp->name);
	ft_stringkil(tmp->path);
	free(tmp->stats);
	if (tmp->dir != NULL)
		closedir(tmp->dir);
	free(tmp);
}

void			ls_files(t_string *out, t_array *files, t_args *args)
{
	int				i;
	int				max_len;
	t_array			*table;

	if ((max_len = 8) == 8 && FLAG(FLAG_SORT))
		filesort_t(files, args);
	else if (!FLAG(FLAG_F))
		filesort(files);
	if ((i = -1) == -1 && FLAG(FLAG_R))
		ft_arrayrev(files);
	table = init_table(8);
	while (++i < files->length)
	{
		if (hide_file(files, &i, args))
			continue ;
		if (FLAG(FLAG_1))
			ls_file1(table, (t_file*)files->data[i], args);
		while (((t_file*)files->data[i])->name->length >= max_len)
			max_len += 8;
	}
	if (!FLAG(FLAG_1))
		ls_column(out, files, max_len, NULL);
	else
		print_table(out, table);
	ft_arraykil(table, kill_col);
}
