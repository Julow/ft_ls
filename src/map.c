/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/19 11:15:21 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/19 11:15:22 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_map			*ft_mapnew(char *key, void *value)
{
	t_map			*map;

	map = MAL1(t_map);
	map->key = ft_stringnew();
	if (!ft_stringadd(map->key, key))
	{
		ft_stringkil(map->key);
		free(map);
		return (NULL);
	}
	map->value = value;
	return (map);
}

t_map			*ft_mapget(t_array *array, char *key)
{
	int				i;
	t_map			*tmp;

	i = -1;
	while (++i < array->length)
	{
		tmp = (t_map*)(array->data[i]);
		if (ft_strequ(key, tmp->key->content))
			return (tmp);
	}
	return (NULL);
}

int				ft_mapchr(t_array *array, char *key)
{
	int				i;
	t_map			*tmp;

	i = -1;
	while (++i < array->length)
	{
		tmp = (t_map*)(array->data[i]);
		if (ft_strequ(tmp->key->content, key))
			return (i);
	}
	return (-1);
}

t_map			*ft_maprem(t_array *array, char *key)
{
	int				i;
	t_map			*tmp;

	i = -1;
	while (++i < array->length)
	{
		tmp = (t_map*)(array->data[i]);
		if (ft_strequ(tmp->key->content, key))
		{
			ft_arrayrem(array, i);
			return (tmp);
		}
	}
	return (NULL);
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
