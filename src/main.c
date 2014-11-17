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

static void		ls_file(t_array *array, char *name, t_args *args)
{
	t_string		*tmp;

	if (!FLAG(FLAG_AA) && name[0] == '.')
		return;
	else if (!FLAG(FLAG_A) && (ft_strequ(name, ".") || ft_strequ(name, "..")))
		return;
	tmp = ft_stringnew();
	ft_stringadd(tmp, name);
	ft_arrayadd(array, tmp);
}

static void		ls_dir(t_array *files, DIR *dir, t_args *args)
{
	struct dirent	*ent;

	while ((ent = readdir(dir)) != NULL)
		ls_file(files, ent->d_name, args);
}

int				main(int argc, char **argv)
{
	const int		flags[] = {'l', FLAG_L, 'a', FLAG_A, 'A', FLAG_AA, 0};
	t_args			*args;
	DIR				*dir;
	t_string		*output;
	t_array			*files;
	int				i;

	args = get_args(argc, argv, flags);
	output = ft_stringnew();
	i = 0;
	while (i < args->args_count)
	{
		dir = opendir(args->args[i]);
		if (dir == NULL)
		{
			//ls_file(files, args->args[i], args);
			ft_putstr(args->args[i]);
			ft_putchar('\n');
		}
		else
		{
			files = ft_arraynew();
			if (args->args_count > 1)
			{
				if (i > 0)
					ft_stringaddc(output, '\n');
				ft_stringadd(output, args->args[i]);
				ft_stringadd(output, ":\n");
			}
			ls_dir(files, dir, args);
			closedir(dir);
			colum_add(output, files, 150);
		}
		i++;
	}
	ft_stringput(output);
	return (0);
}
