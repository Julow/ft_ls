/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 13:53:29 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/24 13:53:30 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_string		*ft_stringi(int n)
{
	t_string		*tmp;

	tmp = ft_stringnew();
	ft_stringaddi(tmp, n);
	return (tmp);
}

t_string		*ft_strings(char *str)
{
	t_string		*tmp;

	tmp = ft_stringnew();
	ft_stringadd(tmp, str);
	return (tmp);
}

t_string		*ft_stringdup(t_string *str)
{
	t_string		*dup;

	dup = ft_stringnew();
	ft_stringaddl(dup, str->content, str->length);
	return (dup);
}
