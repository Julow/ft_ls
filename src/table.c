/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 10:56:09 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/24 10:56:10 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_col			*col_new()
{
	t_col			*col;

	col = MAL1(t_col);
	col->max_len = 0;
	col->left = TRUE;
	col->lines = ft_arraynew();
	return (col);
}

void			coll_add(t_col *col, t_string *str)
{
	ft_arrayadd(col->lines, str);
	if (str->length > col->max_length)
		col->max_length = str->length;
}

t_array			*init_table(int length)
{
	t_array			*table;

	table = ft_arraynew();
	while (length-- > 0)
		ft_arrayadd(table, col_new());
	return (table);
}

void			print_table(t_string *out, t_array *table)
{
	int				i;
	int				j;
	int				changes;
	t_col			*col;
	t_string		*tmp;

	changes = 1;
	i = -1;
	while (++i >= 0)
	{
		changes = 0;
		j = -1;
		while (++j < table->length)
		{
			col = (t_col*)(t_col*)table->data[j];
			if (col->lines->length <= i && ++changes >= 0)
				break ;
			tmp = (t_string*)col->lines->data[i];
			if (tmp->left)
				ft_stringaddcn(out, ' ', col->max_length - tmp->length + 1);
			ft_stringaddl(out, tmp->content, tmp->length);
			if (!tmp->left && j + 1 < table->length)
				ft_stringaddcn(out, ' ', col->max_length - tmp->length + 1);
		}
	}
}
