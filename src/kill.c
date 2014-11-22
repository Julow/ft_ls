/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 18:42:54 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/22 18:42:55 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			kill_err(void *err)
{
	ft_stringkil(((t_map*)err)->key);
	free(err);
}

void			kill_file(void *file)
{
	t_file			*tmp;

	tmp = (t_file*)((t_map*)file)->value;
	ft_stringkil(((t_map*)file)->key);
	free(tmp->stats);
	ft_stringkil(tmp->path);
	free(tmp);
	free(file);
}
