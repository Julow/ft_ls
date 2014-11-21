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

void			ft_arrayswap(t_array *array, int i1, int i2)
{
	void			*tmp;

	tmp = array->data[i1];
	array->data[i1] = array->data[i2];
	array->data[i2] = tmp;
}

void			ft_arrayrev(t_array *array)
{
	int				i;
	int				middle;

	middle = array->length / 2;
	i = -1;
	while (++i < middle)
		ft_arrayswap(array, i, array->length - i - 1);
}

static time_t	get_value(void *data, t_args *args)
{
	struct stat		*tmp;

	tmp = (struct stat*)data;
	if (FLAG(FLAG_U))
		return (tmp->st_atimespec.tv_sec);
	if (FLAG(FLAG_UU))
		return (tmp->st_birthtimespec.tv_sec);
	return (tmp->st_mtimespec.tv_sec);

}

void			filesort(t_array *files, t_args *args)
{
	int				i;
	int				j;

	i = -1;
	while (++i < files->length)
	{
		j = i;
		while (++j < files->length)
		{
			if (get_value(((t_map*)files->data[j])->value, args) <
				get_value(((t_map*)files->data[i])->value, args))
				ft_arrayswap(files, i, j);
		}
	}
}

void			ft_mapsort(t_array *array)
{
	int				i;
	int				j;

	i = -1;
	while (++i < array->length)
	{
		j = i;
		while (++j < array->length)
		{
			if (ft_strcmp(((t_map*)array->data[i])->key->content,
				((t_map*)array->data[j])->key->content) > 0)
				ft_arrayswap(array, i, j);
		}
	}
}
