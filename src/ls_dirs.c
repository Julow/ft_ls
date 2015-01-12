/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 19:21:31 by jaguillo          #+#    #+#             */
/*   Updated: 2015/01/12 11:47:44 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static void		write_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

static void		check_dirent(struct dirent *ent, t_array *dirs, t_file *file,
	t_args *args)
{
	t_file			*tmp;

	if (args->args_count < 2)
		args->args_count = 2;
	if (FLAG(FLAG_RR) && ent->d_type == DT_DIR && !ft_strequ(file->real, ".") &&
		!ft_strequ(file->real, "..") && (!FLAG(FLAG_L) ||
			(file->stats->st_mode & S_IFMT) != S_IFLNK))
	{
		tmp = MAL1(t_file);
		tmp->name = ft_stringdup(file->name);
		tmp->path = ft_stringdup(file->path);
		tmp->dir = NULL;//opendir(file->path->content);
		tmp->real = ent->d_name;
		tmp->err = 0;
		tmp->stats = MAL1(struct stat);
		ft_memmove(tmp->stats, file->stats, sizeof(struct stat));
		ft_arrayadd(dirs, tmp);
	}
}

static void		ls_dir(t_file *dir, t_args *args, t_file *tmp)
{
	t_array			files;
	t_array			*dirs;
	int				total;
	struct dirent	*ent;

	total = 0;
	ft_arrayini(&files);
	ft_arrayext(&files, dir->stats->st_nlink);
	dirs = (FLAG(FLAG_RR)) ? ft_arraynew() : NULL;
	while (dir->dir != NULL && (ent = readdir(dir->dir)) != NULL)
	{
		if ((tmp = filenew(ent->d_name, dir->path->content, NULL, args)) == NULL)
			continue ;
		total += (is_visible(tmp->real, args)) ? tmp->stats->st_blocks : 0;
		if (is_visible(tmp->real, args))
			ft_arrayadd(&files, tmp);
		check_dirent(ent, dirs, tmp, args);
	}
	if (FLAG(FLAG_L) && files.length > 0)
		write_total(total);
	ls_files(&files, args);
	ft_arrayclr(&files, &kill_file);
	free(files.data);
	if ((dir->dir != NULL && closedir(dir->dir) > 0 && FALSE) || FLAG(FLAG_RR))
		ls_dirs(dirs, args, 1);
}

void			ls_dirs(t_array *dirs, t_args *args, int f)
{
	int				i;
	t_file			*tmp;

	if (FLAG(FLAG_T) || FLAG(FLAG_SS))
		filesort_t(dirs, args);
	else if (!FLAG(FLAG_F))
		filesort(dirs);
	if (FLAG(FLAG_R))
		ft_arrayrev(dirs);
	i = -1;
	while (++i < dirs->length)
	{
		tmp = (t_file*)dirs->data[i];
		tmp->dir = opendir(tmp->path->content);
		tmp->err = errno;
		if (args->args_count > 1 && is_visible(tmp->real, args))
		{
			if (i > 0 || f > 0)
				ft_putchar('\n');
			ft_putlstr(tmp->path->content, tmp->path->length);
			ft_putstr(":\n");
		}
		if (tmp->dir == NULL)
			print_errno(tmp->real, tmp->err);
		ls_dir(tmp, args, NULL);
	}
	ft_arraykil(dirs, &kill_file);
}
