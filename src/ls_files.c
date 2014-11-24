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

static t_string	*get_modes(mode_t mode)
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
	if (mode & (1 << (9 - 3)))
		ft_stringaddc(tmp, (mode & (1 << (12 - 2))) ? 's' : 'x');
	else
		ft_stringaddc(tmp, (mode & (1 << (12 - 1))) ? 'S' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 7))) ? 'r' : '-');
	ft_stringaddc(tmp, (mode & (1 << (9 - 8))) ? 'w' : '-');
	if (mode & (1 << (9 - 3)))
		ft_stringaddc(tmp, (mode & (1 << (12 - 3))) ? 't' : 'x');
	else
		ft_stringaddc(tmp, (mode & (1 << (12 - 1))) ? 'T' : '-');
	return (tmp);
}

static void		ls_file1(t_array *table, t_map *map, t_args *args)
{
	int				j;
	struct stat		*stats;

	j = -1;
	stats = ((t_file*)map->value)->stats;
	if (FLAG(FLAG_L))
	{
		col_add((t_col*)table->data[++j], get_modes(stats->st_mode));
		((t_col*)table->data[j])->left = 2;
		col_add((t_col*)table->data[++j], ft_stringi(stats->st_nlink));
		((t_col*)table->data[j])->left = FALSE;
		col_add((t_col*)table->data[++j],
			ft_strings(getpwuid(stats->st_uid)->pw_name));
		((t_col*)table->data[j])->left = 2;
		col_add((t_col*)table->data[++j],
			ft_strings(getgrgid(stats->st_gid)->gr_name));
		((t_col*)table->data[j])->left = 2;
		col_add((t_col*)table->data[++j], get_minor(stats));
		((t_col*)table->data[j])->left = FALSE;
		col_add((t_col*)table->data[++j], get_major(stats));
		((t_col*)table->data[j])->left = FALSE;
		col_add((t_col*)table->data[++j], get_time(stats->st_mtimespec.tv_sec));
	}
	col_add((t_col*)table->data[++j], get_name(map->key, (t_file*)map->value,
		args));
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

void			kill_file(void *file)
{
	t_file			*tmp;

	tmp = (t_file*)((t_map*)file)->value;
	ft_stringkil(((t_map*)file)->key);
	free(tmp->stats);
	ft_stringkil(tmp->path);
	free(tmp);
	free(file);
}

void			ls_files(t_string *out, t_array *files, t_args *args)
{
	int				i;
	int				max_len;
	t_array			*table;

	if (FLAG(FLAG_SORT))
		filesort(files, args);
	else if (!FLAG(FLAG_F))
		ft_mapsort(files);
	if (FLAG(FLAG_R))
		ft_arrayrev(files);
	table = init_table(8);
	i = -1;
	max_len = 8;
	while (++i < files->length)
	{
		if (FLAG(FLAG_1))
			ls_file1(table, (t_map*)files->data[i], args);
		while (((t_map*)files->data[i])->key->length >= max_len)
			max_len += 8;
	}
	if (!FLAG(FLAG_1))
		ls_column(out, files, max_len);
	else
		print_table(out, table);
	ft_arraykil(table, kill_col);
}
