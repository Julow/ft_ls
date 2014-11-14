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

# define FLAG(m)	((args->flags & m) == m)

# define FLAG_L		(1)
# define FLAG_B		(1 << 1)

typedef struct	s_argv
{
	char			*program;
	char			**args;
	int				flags;
}				t_args;

size_t			ft_tablen(void **array);
t_args			*get_args(int argc, char **argv, int const *flags);

#endif
