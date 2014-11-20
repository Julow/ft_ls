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

static void		ls_errs(t_string *output, t_array *errs, t_args *args)
{
	int				i;
	t_map			*tmp;

	if (!FLAG(FLAG_F))
		ft_mapsort(errs);
	i = -1;
	while (++i < errs->length)
	{
		tmp = (t_map*)errs->data[i];
		ft_stringadd(output, "ls: ");
		ft_stringaddl(output, tmp->key->content, tmp->key->length);
		ft_stringadd(output, ": ");
		ft_stringadd(output, (char*)tmp->value);
		ft_stringaddc(output, '\n');
	}
}

void			*filenew(char *name, char *path, DIR *dir)
{
	t_file			*file;
	struct stat		*stats;

	stats = MAL1(struct stat);
	file = MAL1(t_file);
	file->path = ft_stringnew();
	ft_stringadd(file->path, path);
	while (file->path->content[file->path->length - 1] == '/')
		ft_stringrem(file->path, file->path->length - 1, 1);
	ft_stringaddc(file->path, '/');
	ft_stringadd(file->path, name);
	file->dir = dir;
	if (stat(file->path->content, stats) < 0)
	{
		ft_putstr_fd("ls: ", 2);
		ft_stringputfd(file->path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_stringkil(&(file->path));
		free(file);
		return (NULL);
	}
	file->stats = stats;
	return ((void*)file);
}

void			ls(t_string *output, t_args *args)
{
	t_array			*files;
	t_array			*dirs;
	t_array			*errs;
	DIR				*dir;
	int				i;

	files = ft_arraynew();
	dirs = ft_arraynew();
	errs = ft_arraynew();
	i = -1;
	while (++i < args->args_count)
	{
		dir = opendir(args->args[i]);
		if (dir == NULL && errno == 20)
			ft_arrayadd(files, ft_mapnew(args->args[i],
				filenew(args->args[i], ".", NULL)));
		else if (dir == NULL)
			ft_arrayadd(errs, ft_mapnew(args->args[i], strerror(errno)));
		else
			ft_arrayadd(dirs, ft_mapnew(args->args[i],
				filenew(args->args[i], ".", dir)));
	}
	ls_errs(output, errs, args);
	ft_arraykil(&errs, &free);
	ls_files(output, files, args);
	ls_dirs(output, dirs, args, files->length);
	ft_arraykil(&files, &free);
	ft_arraykil(&dirs, &free);
}

int				main(int argc, char **argv)
{
	t_args			*args;
	t_string		*output;

	args = get_args(argc, argv);
	output = ft_stringnew();
	ls(output, args);
	ft_stringput(output);
	ft_stringkil(&output);
	return (0);
}
