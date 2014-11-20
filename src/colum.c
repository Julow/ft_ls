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

/*
static void		kill_string(void *data)
{
	ft_stringkil((t_string**)&data);
}

static int		get_width(void)
{
	struct ttysize	ts;

	ioctl(0, TIOCGSIZE, &ts);
	return (ts.ts_cols);
}

static void		colum_print(t_string *out, t_array *array, int width, int llen)
{
	t_map			*tmp;
	int				i;
	int				line;
	int				spaces;

	line = 0;
	i = -1;
	while (++i < array->length)
	{
		tmp = (t_map*)array->data[i];
		ft_stringadd(out, tmp->key->content);
		line += llen;
		if (line >= width && i + 1 < array->length)
		{
			line = 0;
			ft_stringaddc(out, '\n');
			continue;
		}
		spaces = tmp->key->length - 1;
		while (++spaces < llen)
			ft_stringaddc(out, ' ');
	}
}

void			colum_add(t_string *output, t_array *array)
{
	t_map			*tmp;
	int				max_len;
	int				i;

	i = -1;
	max_len = 0;
	while (++i < array->length)
	{
		tmp = (t_map*)array->data[i];
		if (tmp->key->length > max_len)
			max_len = tmp->key->length;
	}
	colum_print(output, array, get_width() - max_len, max_len + 7);
	ft_stringext(output, array->length * max_len + 1);
	ft_arrayclr(array, &kill_string);
	ft_stringaddc(output, '\n');
}
*/
