/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:32:52 by jaguillo          #+#    #+#             */
/*   Updated: 2014/11/03 18:32:53 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strncat(char *s1, const char *s2, t_uint n)
{
	t_uint			i;
	t_uint			i2;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	i2 = 0;
	while (s2[i2] != '\0' && i2 < n)
	{
		s1[i + i2] = s2[i2];
		i2++;
	}
	s1[i + i2] = '\0';
	return (s1);
}
