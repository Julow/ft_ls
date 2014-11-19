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

static void		ls_dir(t_string *output, DIR *dir, t_args *args)
{
	t_array			*files;
	struct dirent	*dirent;

	files = ft_arraynew();
	while ((dirent = readdir(dir)) != NULL)
		ft_arrayadd(files, ft_mapnew(dirent->d_name, NULL));
	ls_files(output, files, args);
	ft_arraykil(&files, &free);
}

void			ls_dirs(t_string *output, t_array *dirs, t_args *args, int f)
{
	int				i;
	t_map			*tmp;

	if (FLAG(FLAG_T))
	{
//
	}
	else if (!FLAG(FLAG_F))
		ft_mapsort(dirs);
	i = -1;
	while (++i < dirs->length)
	{
		tmp = (t_map*)dirs->data[i];
		if (args->args_count > 1)
		{
			if (i > 0 || f > 0)
				ft_stringaddc(output, '\n');
			ft_stringadd(output, tmp->key);
			ft_stringadd(output, ":\n");
		}
		ls_dir(output, (DIR*)tmp->value, args);
	}
}
