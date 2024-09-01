/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:25:49 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 21:52:52 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdint.h>

static unsigned long long	ft_nb(const char *str, unsigned long long nb, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

unsigned long long	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					i;
	int					s;

	nb = 0;
	i = 0;
	s = 1;
	while (str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == ' ')
	i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			s = -1;
		i++;
	}
	if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		return (0);
	nb = ft_nb(str, nb, i);
	return (s * nb);
}
