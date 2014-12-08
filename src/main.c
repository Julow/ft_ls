/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:50:34 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/12 14:50:34 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

void			*filenew(char *name, char *path, DIR *dir, t_args *args)
{
	t_file			*file;

	file = MAL1(t_file);
	file->stats = MAL1(struct stat);
	file->path = ft_stringnew();
	ft_stringadd(file->path, path);
	while (file->path->length > 1 &&
		file->path->content[file->path->length - 1] == '/')
		ft_stringrem(file->path, file->path->length - 1, 1);
	if (file->path->length > 0 && name[0] != '/' &&
		file->path->content[file->path->length - 1] != '/')
		ft_stringaddc(file->path, '/');
	ft_stringadd(file->path, name);
	file->dir = dir;
	file->name = NULL;
	if (lstat(file->path->content, file->stats) < 0)
	{
		print_errno(name, errno);
		kill_file(file);
		return (NULL);
	}
	file->name = get_name(file, name, args);
	file->real = name;
	return ((void*)file);
}

static void		ls_args(t_array *files, t_array *dirs, t_array *errs,
	t_args *args)
{
	int				i;
	int				e;
	DIR				*dir;
	t_file			*tmp;

	i = -1;
	while (++i < args->args_count)
	{
		dir = opendir(args->args[i]);
		e = errno;
		if (dir == NULL && errno != 20)
			return ((void)ft_arrayadd(errs, ft_pairnew((args->args[i][0] ==
			'\0') ? "fts_open" : args->args[i], strerror(errno))));
		tmp = filenew(args->args[i], "", dir, args);
		tmp->err = e;
		if (dir != NULL && !FLAG(FLAG_D) && (!FLAG(FLAG_L) ||
			(tmp->stats->st_mode & S_IFMT) != S_IFLNK))
			ft_arrayadd(dirs, tmp);
		else
			ft_arrayadd(files, tmp);
	}
}

void			ls(t_args *args)
{
	t_array			*files;
	t_array			*dirs;
	t_array			*errs;

	files = ft_arraynew();
	dirs = ft_arraynew();
	errs = ft_arraynew();
	ls_args(files, dirs, errs, args);
	ls_errs(errs, args);
	ls_files(files, args);
	ls_dirs(dirs, args, files->length);
	ft_arraykil(files, &kill_file);
}

int				main(int argc, char **argv)
{
	t_args			*args;

	args = get_args(argc, argv);
	ls(args);
	kill_args(&args);
	return (0);
}
