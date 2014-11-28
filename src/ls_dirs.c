/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dirs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 19:21:31 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/19 19:21:32 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		write_total(t_string *output, int total)
{
	ft_stringadd(output, "total ");
	ft_stringaddi(output, total);
	ft_stringaddc(output, '\n');
}

static void		check_dirent(struct dirent *ent, t_array *dirs, t_file *tmp,
	t_args *args)
{
	if (args->args_count < 2)
		args->args_count = 2;
	if (FLAG(FLAG_RR) && ent->d_type == DT_DIR &&
		!ft_strequ(tmp->name->content, ".") &&
		!ft_strequ(tmp->name->content, ".."))
	{
		tmp->dir = opendir(tmp->path->content);
		ft_arrayadd(dirs, tmp);
	}
	else
		kill_file(tmp);
}

static void		ls_dir(t_string *output, t_file *dir, t_args *args)
{
	t_array			*files;
	t_array			*dirs;
	int				total;
	struct dirent	*ent;
	t_file			*tmp;

	total = 0;
	files = ft_arraynew();
	dirs = (FLAG(FLAG_RR)) ? ft_arraynew() : NULL;
	while ((ent = readdir(dir->dir)) != NULL)
	{
		tmp = filenew(ent->d_name, dir->path->content, NULL, args);
		if ((FLAG(FLAG_AA) || !(tmp->name->content[0] == '.')) && (FLAG(FLAG_A)
			|| (!ft_strequ(tmp->name->content, ".") &&
				!ft_strequ(tmp->name->content, ".."))))
			total += tmp->stats->st_blocks;
		ft_arrayadd(files, tmp);
		check_dirent(ent, dirs, filenew(ent->d_name, dir->path->content, NULL,
			args), args);
	}
	if (FLAG(FLAG_L))
		write_total(output, total);
	ls_files(output, files, args);
	ft_arraykil(files, &kill_file);
	if (FLAG(FLAG_RR))
		ls_dirs(output, dirs, args, 1);
}

void			ls_dirs(t_string *output, t_array *dirs, t_args *args, int f)
{
	int				i;
	t_file			*tmp;

	if (FLAG(FLAG_SORT))
		filesort_t(dirs, args);
	else if (!FLAG(FLAG_F))
		filesort(dirs);
	if (FLAG(FLAG_R))
		ft_arrayrev(dirs);
	i = -1;
	while (++i < dirs->length)
	{
		tmp = (t_file*)dirs->data[i];
		if (args->args_count > 1)
		{
			if (i > 0 || f > 0)
				ft_stringaddc(output, '\n');
			ft_stringaddl(output, tmp->path->content, tmp->path->length);
			ft_stringadd(output, ":\n");
		}
		ls_dir(output, tmp, args);
	}
	ft_arraykil(dirs, &kill_file);
}
