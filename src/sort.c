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

static t_long	get_value(t_file *file, t_args *args)
{
	if (FLAG(FLAG_U))
		return ((t_long)file->stats->st_atimespec.tv_sec);
	if (FLAG(FLAG_UU))
		return ((t_long)file->stats->st_birthtimespec.tv_sec);
	if (FLAG(FLAG_SS))
		return ((t_long)file->stats->st_size);
	return ((t_long)file->stats->st_mtimespec.tv_sec);
}

void			filesort_t(t_array *files, t_args *args)
{
	int				i;
	int				j;
	t_long			tmp1;
	t_long			tmp2;

	i = -1;
	while (++i < files->length)
	{
		j = i;
		while (++j < files->length)
		{
			tmp1 = get_value((t_file*)files->data[i], args);
			tmp2 = get_value((t_file*)files->data[j], args);
			if ((tmp1 == tmp2 &&
				ft_strcmp(((t_file*)files->data[i])->name->content,
				((t_file*)files->data[j])->name->content) > 0) ||
				(tmp1 != tmp2 && tmp1 < tmp2))
				ft_arrayswap(files, i, j);
		}
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
