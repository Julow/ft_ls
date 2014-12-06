/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 12:22:35 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/13 12:22:46 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

int				g_flags[] = {
	'a', FLAG_A, 0,
	'A', FLAG_AA, 0,
	'f', FLAG_F, FLAG_T,
	'1', FLAG_1, FLAG_L,
	'r', FLAG_R, 0,
	'l', FLAG_L, FLAG_1,
	'F', FLAG_FF, 0,
	't', FLAG_T, 0,
	'g', FLAG_G, FLAG_1,
	'o', FLAG_O, FLAG_1,
	'R', FLAG_RR, 0,
	'u', FLAG_U, FLAG_U | FLAG_UU | FLAG_SS | FLAG_C,
	'U', FLAG_UU, FLAG_U | FLAG_UU | FLAG_SS | FLAG_C,
	'n', FLAG_N, 0,
	'd', FLAG_D, 0,
	'S', FLAG_SS, FLAG_U | FLAG_UU | FLAG_SS | FLAG_C,
	'c', FLAG_C, FLAG_U | FLAG_UU | FLAG_SS | FLAG_C,
	'p', FLAG_P, 0,
	'T', FLAG_TT, 0,
	0
};

static void		add_arg(t_args *targs, char *add)
{
	char			**tmp;
	int				i;

	tmp = targs->args;
	targs->args = MAL(char*, targs->args_count + 2);
	i = 0;
	while (tmp[i] != NULL)
	{
		targs->args[i] = tmp[i];
		i++;
	}
	free(tmp);
	targs->args[i] = ft_strdup(add);
	targs->args[i + 1] = NULL;
	targs->args_count++;
}

static void		read_flags(t_args *args, char *str, char *arg0)
{
	int				i;

	while (*(++str) != '\0')
	{
		i = -3;
		while (g_flags[(i += 3)] != 0)
		{
			if (((char)g_flags[i]) == *str)
			{
				args->flags = args->flags & (g_flags[i + 2] ^ 0xFFFFFFFF);
				args->flags = args->flags | g_flags[i + 1];
				break ;
			}
		}
		if (g_flags[i] == 0)
		{
			ft_putstr_fd(arg0, 2);
			ft_putstr_fd(": illegal option -- ", 2);
			ft_putchar_fd(*str, 2);
			ft_putstr_fd("\nusage: ft_ls [-AFRTUacdfglnoprtu1] [file ...]\n", 2);
			exit(2);
		}
	}
}

void			kill_args(t_args **args)
{
	int				i;

	i = -1;
	while (++i < (*args)->args_count)
		free((*args)->args[i]);
	free((*args)->args);
	free(*args);
	*args = NULL;
}

t_args			*get_args(int argc, char **argv)
{
	t_args			*args;

	args = MAL1(t_args);
	args->args = MAL1(char*);
	args->args[0] = NULL;
	args->args_count = 0;
	args->flags = 0;
	while (--argc > 0 && argv++)
		if (ft_strequ(*argv, "--"))
			break ;
		else if (**argv == '-' && *(*argv + 1) != '\0')
			read_flags(args, *argv, *argv);
		else
		{
			add_arg(args, *argv);
			break ;
		}
	while (--argc > 0 && argv++)
		add_arg(args, *argv);
	if (args->args_count == 0)
		add_arg(args, ".");
	return (args);
}
