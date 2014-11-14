/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 16:17:06 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/14 16:17:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t			ft_tablen(void **array)
{
	void			**tmp;

	tmp = array;
	while (*tmp != NULL)
		tmp++;
	return (tmp - array);
}
