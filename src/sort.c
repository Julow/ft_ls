/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/18 14:30:09 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/18 14:30:11 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_bool	file_cmp(t_file *f1, t_file *f2, t_args *args)
{
	if (FLAG(FLAG_T | FLAG_U) && f1->stats->st_atimespec.tv_sec !=
		f2->stats->st_atimespec.tv_sec)
		return ((f1->stats->st_atimespec.tv_sec <
		f2->stats->st_atimespec.tv_sec) ? TRUE : FALSE);
	else if (FLAG(FLAG_T | FLAG_UU) && f1->stats->st_birthtimespec.tv_sec
		!= f2->stats->st_birthtimespec.tv_sec)
		return ((f1->stats->st_birthtimespec.tv_sec <
		f2->stats->st_birthtimespec.tv_sec) ? TRUE : FALSE);
	else if (FLAG(FLAG_T | FLAG_C) && f1->stats->st_ctimespec.tv_sec !=
		f2->stats->st_ctimespec.tv_sec)
		return ((f1->stats->st_ctimespec.tv_sec <
		f2->stats->st_ctimespec.tv_sec) ? TRUE : FALSE);
	else if (FLAG(FLAG_SS) && f1->stats->st_size != f2->stats->st_size)
		return ((f1->stats->st_size < f2->stats->st_size) ? TRUE : FALSE);
	else if (FLAG(FLAG_T) && (args->flags & (FLAG_U | FLAG_UU | FLAG_C)) == 0  &&
		f1->stats->st_mtimespec.tv_sec != f2->stats->st_mtimespec.tv_sec)
		return ((f1->stats->st_mtimespec.tv_sec <
		f2->stats->st_mtimespec.tv_sec) ? TRUE : FALSE);
	return ((ft_strcmp(f1->name->content, f2->name->content) > 0) ? TRUE : 0);
}

void			filesort_t(t_array *fls, t_args *args)
{
	int				i;
	int				j;

	i = -1;
	while (++i < fls->length)
	{
		j = i;
		while (++j < fls->length)
			if (file_cmp((t_file*)fls->data[i], (t_file*)fls->data[j], args))
				ft_arrayswap(fls, i, j);
	}
}

void			filesort(t_array *files)
{
	int				i;
	int				j;
	t_file			*tmpi;
	t_file			*tmpj;

	i = -1;
	while (++i < files->length)
	{
		tmpi = (t_file*)files->data[i];
		j = i;
		while (++j < files->length)
		{
			tmpj = (t_file*)files->data[j];
			if (ft_strcmp(tmpi->name->content, tmpj->name->content) > 0)
			{
				ft_arrayswap(files, i, j);
				tmpi = (t_file*)files->data[i];
			}
		}
	}
}
