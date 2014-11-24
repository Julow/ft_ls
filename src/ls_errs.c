/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_errs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 19:20:37 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/24 19:20:37 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		kill_err(void *err)
{
	ft_stringkil(((t_map*)err)->key);
	free(err);
}

void			ls_errs(t_string *output, t_array *errs, t_args *args)
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
	ft_arraykil(errs, &kill_err);
}
