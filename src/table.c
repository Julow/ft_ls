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

static int		get_line_count(t_array *table)
{
	int				i;
	int				lines;

	lines = 0;
	i = -1;
	while (++i < table->length)
	{
		if (((t_col*)table->data[i])->lines->length > lines)
			lines = ((t_col*)table->data[i])->lines->length;
	}
	return (lines);
}

void			kill_col(void *col)
{
	ft_arraykil(((t_col*)col)->lines, &ft_stringkil);
	free(col);
}

void			col_add(t_col *col, t_string *str)
{
	ft_arrayadd(col->lines, str);
	if (str->length > col->max_length)
		col->max_length = str->length;
}

t_array			*init_table(int length)
{
	t_array			*table;
	t_col			*tmp;

	table = ft_arraynew();
	while (length-- > 0)
	{
		tmp = MAL1(t_col);
		tmp->max_length = 0;
		tmp->left = TRUE;
		tmp->lines = ft_arraynew();
		ft_arrayadd(table, tmp);
	}
	return (table);
}

void			print_table(t_array *table)
{
	int const		length = get_line_count(table);
	int				i;
	int				j;
	t_col			*col;
	t_string		*tmp;

	i = -1;
	while (++i < length && (j = -1) == -1)
	{
		while (++j < table->length)
		{
			col = (t_col*)table->data[j];
			if (col->lines->length <= i || col->max_length <= 0)
				continue;
			tmp = (t_string*)col->lines->data[i];
			ft_putnchar(' ', (col->left <= 0) ?
				col->max_length - tmp->length - col->left : 0);
			ft_putlstr(tmp->content, tmp->length);
			if (col->left > 0 && j + 1 < table->length)
				ft_putnchar(' ', col->max_length - tmp->length);
			if (j + 1 < table->length)
				ft_putnchar(' ', (col->left > 0) ? col->left : 1);
		}
		ft_putchar('\n');
	}
}
