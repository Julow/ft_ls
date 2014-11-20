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

void			ft_mapsort(t_array *array)
{
	int				i;
	int				j;
	int				small;
	int				small_i;
	int				diff;

	i = -1;
	while (++i < array->length)
	{
		small = 0;
		small_i = i;
		j = i;
		while (++j < array->length)
		{
			diff = ft_strcmp(((t_map*)(array->data[j]))->key->content,
				((t_map*)(array->data[i]))->key->content);
			if (diff < small)
			{
				small_i = j;
				small = diff;
			}
		}
		if (small_i > i)
			ft_arrayswap(array, small_i, i);
	}
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
	time_t			small;
	int				small_i;
	time_t			tmp;

	i = -1;
	while (++i < files->length)
	{
		small = get_value(((t_map*)files->data[i])->value, args);
		small_i = i;
		j = i;
		while (++j < files->length)
		{
			tmp = get_value(((t_map*)files->data[j])->value, args);
			if (tmp < small)
			{
				small = tmp;
				small_i = j;
			}
		}
		if (small_i != i)
			ft_arrayswap(files, small_i, i);
	}
}
