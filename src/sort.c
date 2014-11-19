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

static void		ft_arrayswap(t_array *array, int i1, int i2)
{
	void			*tmp;

	tmp = array->data[i1];
	array->data[i1] = array->data[i2];
	array->data[i2] = tmp;
}

void			ft_mapsort(t_array *array)
{
	int				i;
	int				j;
	int				small;
	int				small_i;
	int				diff;

	small_i = 0;
	i = -1;
	while (++i < array->length)
	{
		small = 0;
		j = i;
		while (++j < array->length)
		{
			diff = ft_strcmp(((t_map*)(array->data[j]))->key,
				((t_map*)(array->data[i]))->key);
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
