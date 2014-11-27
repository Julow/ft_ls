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

static t_time	get_value(void *data, t_args *args)
{
	t_file		*tmp;

	tmp = (t_file*)data;
	if (FLAG(FLAG_U))
		return (tmp->stats->st_atimespec);
	if (FLAG(FLAG_UU))
		return (tmp->stats->st_birthtimespec);
	return (tmp->stats->st_mtimespec);
}

void			filesort_t(t_array *files, t_args *args)
{
	int				i;
	int				j;
	t_time			tmp1;
	t_time			tmp2;

	i = -1;
	while (++i < files->length)
	{
		j = i;
		while (++j < files->length)
		{
			tmp1 = get_value(((t_map*)files->data[i])->value, args);
			tmp2 = get_value(((t_map*)files->data[j])->value, args);
			if ((tmp1.tv_sec == tmp2.tv_sec &&
				ft_strcmp(((t_map*)files->data[i])->key->content,
				((t_map*)files->data[j])->key->content) > 0) ||
				(tmp1.tv_sec != tmp2.tv_sec && tmp1.tv_sec < tmp2.tv_sec))
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
				ft_arrayswap(files, i, j);
		}
	}
}
