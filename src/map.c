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
	map->key = key;
	map->key_length = ft_strlen(key);
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
		if (ft_strequ(key, tmp->key))
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
		if (ft_strequ(tmp->key, key))
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
		if (ft_strequ(tmp->key, key))
		{
			ft_arrayrem(array, i);
			return (tmp);
		}
	}
	return (NULL);
}
