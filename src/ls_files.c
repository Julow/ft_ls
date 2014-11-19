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

static void		ls_file(t_string *output, char *name, t_args *args)
{
	ft_stringadd(output, name);
	ft_stringaddc(output, '\n');
	(void)args;
}

void			ls_files(t_string *output, t_array *files, t_args *args)
{
	int				i;
	char			*tmp;

	if (FLAG(FLAG_T))
	{
//
	}
	else if (!FLAG(FLAG_F))
		ft_mapsort(files);
	i = -1;
	while (++i < files->length)
	{
		tmp = ((t_map*)files->data[i])->key;
		if (!FLAG(FLAG_A) && (ft_strequ(tmp, ".") || ft_strequ(tmp, "..")))
			continue;
		else if (!FLAG(FLAG_AA) && (tmp[0] == '.'))
			continue;
		ls_file(output, tmp, args);
	}
}
