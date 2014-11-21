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
		ft_stringadd(output, "ft_ls: ");
		ft_stringaddl(output, tmp->key->content, tmp->key->length);
		ft_stringadd(output, ": ");
		ft_stringadd(output, (char*)tmp->value);
		ft_stringaddc(output, '\n');
	}
	ft_arraykil(&errs, &free);
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
				filenew(args->args[i], "", NULL)));
		else
			ft_arrayadd((dir == NULL) ? errs : dirs, ft_mapnew(args->args[i],
				(dir == NULL) ? strerror(errno) : filenew(args->args[i], "",
					dir)));
	}
	ls_errs(output, errs, args);
	ls_files(output, files, args);
	ls_dirs(output, dirs, args, files->length);
	ft_arraykil(&files, &free);
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
