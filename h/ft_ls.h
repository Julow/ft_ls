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
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <string.h>

# define FLAG(m)	((args->flags & (m)) == (m))

# define FLAG_SORT	(1 << 31)
# define FLAG_L		((1) | FLAG_1)
# define FLAG_A		((1 << 1) | FLAG_AA)
# define FLAG_AA	(1 << 2)
# define FLAG_D		(1 << 3)
# define FLAG_1 	(1 << 4)
# define FLAG_RR 	(1 << 5)
# define FLAG_R 	(1 << 6)
# define FLAG_T 	((1 << 7) | FLAG_SORT)
# define FLAG_F		((1 << 8) | FLAG_A)
# define FLAG_U		((1 << 9) | FLAG_SORT)
# define FLAG_UU	((1 << 10) | FLAG_SORT)
# define FLAG_G		(1 << 11)

typedef struct timespec		t_time;

typedef long long int		t_ulong;

typedef struct	s_map
{
	t_string		*key;
	void			*value;
}				t_map;

typedef struct	s_col
{
	int				max_length;
	t_bool			left;
	t_array			*lines;
}				t_col;

typedef struct	s_file
{
	t_string		*path;
	DIR				*dir;
	struct stat		*stats;
}				t_file;

typedef struct	s_argv
{
	char			*program;
	char			**args;
	int				args_count;
	int				flags;
}				t_args;

/*
** kill.c
*/
void			kill_err(void *err);
void			kill_file(void *file);
void			kill_col(void *col);

/*
** map.c
*/
t_map			*ft_mapnew(char *key, void *value);
t_map			*ft_mapget(t_array *array, char *key);
int				ft_mapchr(t_array *array, char *key);
t_map			*ft_maprem(t_array *array, char *key);

/*
** ls_files.c
*/
void			ls_files(t_string *output, t_array *files, t_args *args);

/*
** ls_files.c
*/
void			ls_dirs(t_string *output, t_array *dirs, t_args *args, int f);

/*
** main.c
*/
void			ls(t_string *output, t_args *args);

/*
** argv.c
*/
void			kill_args(t_args *args);
t_args			*get_args(int argc, char **argv);

/*
** utils.c
*/
t_string		*get_time(time_t m_time);
void			*filenew(char *name, char *path, DIR *dir);

/*
** sort.c
*/
void			ft_mapsort(t_array *array);
void			filesort(t_array *files, t_args *args);
void			dirsort(t_array *dirs, t_args *args);

/*
** table.c
*/
t_col			*col_new();
t_array			*init_table(int length);
void			print_table(t_string *out, t_array *table);

#endif
