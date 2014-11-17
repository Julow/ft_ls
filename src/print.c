/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/17 18:22:56 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/17 18:22:59 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		kill_string(void *data)
{
	t_string		*tmp;

	tmp = (t_string*)data;
	ft_stringkil(&tmp);
}

void			colum_add(t_string *output, t_array *array, int width)
{
	t_string		*tmp;
	int				max_len;
	int				i;
	int				line;
	int				spaces;

	i = -1;
	max_len = 5;
	while (++i < array->length)
	{
		tmp = (t_string*)array->data[i];
		if (tmp->length > max_len)
			max_len = tmp->length;
	}
	max_len += 7;
	ft_stringext(output, array->length * max_len + 1);
	line = 0;
	i = -1;
	while (++i < array->length)
	{
		tmp = (t_string*)array->data[i];
		ft_stringadd(output, tmp->content);
		line += max_len;
		if (line >= width && i + 1 < array->length)
		{
			line = 0;
			ft_stringaddc(output, '\n');
			continue;
		}
		spaces = tmp->length - 1;
		while (++spaces < max_len)
			ft_stringaddc(output, ' ');
	}
	ft_arrayclr(array, &kill_string);
	ft_stringaddc(output, '\n');
}
