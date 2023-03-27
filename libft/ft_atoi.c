/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:25:49 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/30 14:50:02 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb(const char *str, int nb, int i)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		nb;
	int		s;

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
