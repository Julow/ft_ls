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
# include <dirent.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <string.h>

# define FLAG(m)	((args->flags & (m)) == (m))

# define MONTH(m)	((m) * 30 * 24 * 60 * 60)

# define FLAG_L		((1) | FLAG_1)
# define FLAG_A		((1 << 1) | FLAG_AA)
# define FLAG_AA	(1 << 2)
# define FLAG_D		(1 << 3 | FLAG_A)
# define FLAG_1 	(1 << 4)
# define FLAG_RR 	(1 << 5)
# define FLAG_R 	(1 << 6)
# define FLAG_T 	((1 << 7))
# define FLAG_F		((1 << 8) | FLAG_A)
# define FLAG_U		((1 << 9))
# define FLAG_UU	((1 << 10))
# define FLAG_G		(1 << 11 | FLAG_L)
# define FLAG_FF	(1 << 12)
# define FLAG_O		(1 << 14 | FLAG_L)
# define FLAG_N		(1 << 15 | FLAG_L)
# define FLAG_SS	(1 << 16)
# define FLAG_C		(1 << 17)
# define FLAG_P		(1 << 19)
# define FLAG_TT	(1 << 20)

# define MAJOR(dev)	((int)(((unsigned int)(dev) >> 24) & 0xFF))
# define MINOR(dev)	((int)((dev) & 0xFFFFFF))

typedef struct timespec		t_time;

typedef struct stat			t_stat;

typedef struct	s_col
{
	int				max_length;
	int				left;
	t_array			*lines;
}				t_col;

typedef struct	s_file
{
	char			*real;
	t_string		*name;
	t_string		*path;
	DIR				*dir;
	struct stat		*stats;
	int				err;
}				t_file;

typedef struct	s_argv
{
	char			**args;
	int				args_count;
	int				flags;
}				t_args;

/*
** ls_errs.c
*/
void			print_errno(char *name, int no);
void			ls_errs(t_array *errs, t_args *args);

/*
** ls_files.c
*/
void			ls_files(t_array *files, t_args *args);

/*
** ls_files.c
*/
void			kill_file(void *file);
void			ls_dirs(t_array *dirs, t_args *args, int f);

/*
** main.c
*/
void			*filenew(char *name, char *path, DIR *dir, t_args *args);
void			ls(t_args *args);

/*
** argv.c
*/
void			kill_args(t_args **args);
t_args			*get_args(int argc, char **argv);

/*
** utils.c
** statutils.c
*/
t_string		*ft_stringi(int n);
t_string		*get_name(t_file *file, char *name, t_args *args);
t_bool			is_visible(char *name, t_args *args);
t_string		*get_time(t_file *file, t_args *args);

t_string		*get_pwuid(uid_t id, t_args *args);
t_string		*get_grgid(uid_t id, t_args *args);
t_string		*get_minor(struct stat *s);
t_string		*get_major(struct stat *s);
char			get_special_mode(mode_t ifmt);

/*
** sort.c
*/
void			filesort_t(t_array *files, t_args *args);
void			filesort(t_array *files);

/*
** table.c
*/
void			col_add(t_col *col, t_string *str);
t_array			*init_table(int length);
void			kill_col(void *col);
void			print_table(t_array *table);

#endif
