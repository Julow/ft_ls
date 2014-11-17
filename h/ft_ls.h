/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 16:00:24 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/12 16:00:25 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>

# define FLAG(m)	((args->flags & m) == m)

# define FLAG_L		(1)
# define FLAG_A		((1 << 2) + (1 << 1))
# define FLAG_AA	(1 << 2)

typedef struct	s_argv
{
	char			*program;
	char			**args;
	int				args_count;
	int				flags;
}				t_args;

t_args			*get_args(int argc, char **argv, int const *flags);

void			colum_add(t_string *output, t_array *array, int width);

#endif
