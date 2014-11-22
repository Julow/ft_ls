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

static void		ls_dir(t_string *output, t_map *dir, t_args *args)
{
	t_array			*files;
	int				total;
	struct dirent	*ent;
	t_file			*tmp;

	total = 0;
	files = ft_arraynew();
	while ((ent = readdir(((t_file*)dir->value)->dir)) != NULL)
	{
		if ((!FLAG(FLAG_A) && (ft_strequ(ent->d_name, ".")
			|| ft_strequ(ent->d_name, ".."))) || (!FLAG(FLAG_AA)
			&& (ent->d_name[0] == '.')))
			continue;
		tmp = filenew(ent->d_name, ((t_file*)dir->value)->path->content, NULL);
		total += tmp->stats->st_blocks;
		ft_arrayadd(files, ft_mapnew(ent->d_name, tmp));
	}
	if (FLAG(FLAG_L))
	{
		ft_stringadd(output, "total ");
		ft_stringaddi(output, total);
		ft_stringaddc(output, '\n');
	}
	ls_files(output, files, args);
	ft_arraykil(&files, &kill_file);
}

void			ls_dirs(t_string *output, t_array *dirs, t_args *args, int f)
{
	int				i;
	t_map			*tmp;

	if (FLAG(FLAG_SORT))
		filesort(dirs, args);
	else if (!FLAG(FLAG_F))
		ft_mapsort(dirs);
	if (FLAG(FLAG_R))
		ft_arrayrev(dirs);
	i = -1;
	while (++i < dirs->length)
	{
		tmp = (t_map*)dirs->data[i];
		if (args->args_count > 1)
		{
			if (i > 0 && f > 1)
				ft_stringaddc(output, '\n');
			ft_stringaddl(output, tmp->key->content, tmp->key->length);
			ft_stringadd(output, ":\n");
		}
		ls_dir(output, tmp, args);
	}
	ft_arraykil(&dirs, &kill_file);
}
