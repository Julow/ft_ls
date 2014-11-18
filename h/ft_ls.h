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
# include <errno.h>
# include <unistd.h>
# include <strings.h>
# include <sys/ioctl.h>

# define FLAG(m)	((args->flags & m) == m)

# define FLAG_L		(1)
# define FLAG_A		((1 << 2) + (1 << 1))
# define FLAG_AA	(1 << 2)
# define FLAG_D		(1 << 3)

typedef struct	s_argv
{
	char			*program;
	char			**args;
	int				args_count;
	int				flags;
}				t_args;

typedef struct	s_file
{
	char			*name;
}				t_file;

typedef struct	s_fdir
{
	char			*name;
	DIR				*dir;
}				t_fdir;

t_args			*get_args(int argc, char **argv);

void			colum_add(t_string *output, t_array *array);

void			stringsort(t_array *array);

#endif
