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

static void		ls(t_string *out, t_args *args)
{
	t_array			*errs;
	t_array			*files;
	t_array			*dirs;
	int				i;

	//
	stringsort(errs);
	i = -1;
	while (++i < errs->length)
	{
		ft_stringadd(out, ((t_string*)(errs->data[i]))->content);
		ft_stringkil((t_string**)&(errs->data[i]));
	}
	ft_arraykil(&errs, NULL);
}

int				main(int argc, char **argv)
{
	t_args			*args;
	t_string		*out;

	args = get_args(argc, argv);
	out = ft_stringnew();
	ls(out, args);
	ft_stringput(out);
	ft_stringkil(&out);
	return (0);
}
