/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:50:34 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/12 14:50:34 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				main(int argc, char **argv)
{
	const int		flags[] = {'l', FLAG_L, 'b', FLAG_B, 0};
	t_args			*args;
	int				i;

	args = get_args(argc, argv, flags);
	ft_putstr("files to read: ");
	i = 0;
	while (args->args[i] != NULL)
	{
		ft_putstr(args->args[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putstr("\nflags: ");
	i = 32;
	while (i-- > 0)
		ft_putnbr(args->flags >> i & 1);
	ft_putstr("\n");
	return (0);
}
