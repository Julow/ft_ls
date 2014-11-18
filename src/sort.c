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

void			stringsort(t_array *array)
{
	t_string		*tmp1;
	t_string		*tmp2;
	int				i;

	i = 0;
	while (++i < array->length)
	{
		tmp1 = (t_string*)(array->data[i - 1]);
		tmp2 = (t_string*)(array->data[i]);
		if (ft_strcmp(tmp1->content, tmp2->content) < 0)
		{
			array->data[i - 1] = tmp2;
			array->data[i] = tmp1;
			i = 0;
		}
	}
}
