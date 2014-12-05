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
#include <stdlib.h>

static void		kill_err(void *err)
{
	ft_stringkil(((t_pair*)err)->key);
	free(err);
}

void			print_errno(char *name)
{
	ft_putstr_fd("ft_ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

void			ls_errs(t_array *errs, t_args *args)
{
	int				i;
	t_pair			*tmp;

	if (!FLAG(FLAG_F))
		ft_pairsort(errs);
	i = -1;
	while (++i < errs->length)
	{
		tmp = (t_pair*)errs->data[i];
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(tmp->key->content, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd((char*)tmp->value, 2);
		ft_putchar_fd('\n', 2);
	}
	ft_arraykil(errs, &kill_err);
}
