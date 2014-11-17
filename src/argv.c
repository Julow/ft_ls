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

static void		add_arg(t_args *args, char *add)
{
	char			**tmp;
	int				i;

	tmp = args->args;
	args->args = MAL(char*, ft_tablen((void**)tmp) + 2);
	i = 0;
	while (tmp[i] != NULL)
	{
		args->args[i] = tmp[i];
		i++;
	}
	free(tmp);
	args->args[i] = ft_strdup(add);
	args->args[i + 1] = NULL;
	args->args_count++;
}

static void		read_flags(t_args *args, char *str, int const *flags)
{
	int				i;

	while (*(++str) != '\0')
	{
		i = -2;
		while (flags[(i += 2)] != 0)
		{
			if (((char)flags[i]) == *str)
			{
				args->flags = args->flags | flags[i + 1];
				break ;
			}
		}
		if (flags[i] == 0)
		{
			ft_putstr_fd(args->program, 2);
			ft_putstr_fd(": illegal option -- ", 2);
			ft_putchar_fd(*str, 2);
			ft_putstr_fd("\nusage: ft_ls [-bl] [file ...]\n", 2);
			exit(2);
		}
	}
}

t_args			*get_args(int argc, char **argv, int const *flags)
{
	t_args			*args;

	args = MAL1(t_args);
	args->program = ft_strdup(*argv);
	args->args = ft_memalloc(1);
	args->args_count = 0;
	args->flags = 0;
	while (--argc > 0 && argv++)
	{
		if (ft_strequ(*argv, "--"))
			break ;
		if (**argv == '-')
			read_flags(args, *argv, flags);
		else
		{
			add_arg(args, *argv);
			break ;
		}
	}
	while (--argc > 0 && argv++)
		add_arg(args, *argv);
	if (ft_tablen((void**)args->args) == 0)
		add_arg(args, ".");
	return (args);
}
