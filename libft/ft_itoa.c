/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:39:42 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/30 14:50:56 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*minint(char *p, int nb, int n, int count)
{
	n = 214748364;
	nb = n;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	p = malloc(12);
	if (!p)
		return (NULL);
	p[count + 2] = '\0';
	p[count + 1] = '8';
	while (count > 0)
	{
		p[count] = nb % 10 + 48;
		nb = nb / 10;
		count--;
	}
	p[count] = '-';
	return (p);
}

static char	*ft_negatif(char *p, int nb, int n, int count)
{
	n = n * -1;
	nb = n;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	p = malloc(sizeof(char) * (count + 2));
	if (!p)
		return (NULL);
	p[count + 1] = '\0';
	while (count > 0)
	{
		p[count] = nb % 10 + 48;
		nb = nb / 10;
		count--;
	}
	p[count] = '-';
	return (p);
}

static char	*ft_pos(char *p, int nb, int n, int count)
{
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	p = malloc(sizeof(char) * count + 1);
	if (!p)
		return (NULL);
	p[count] = '\0';
	while (count > 0)
	{
		p[count - 1] = nb % 10 + 48;
		nb = nb / 10;
		count--;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		i;
	int		count;
	char	*p;
	int		nb;

	nb = n;
	i = 0;
	count = 0;
	if (nb == 0)
	{
		p = malloc(2);
		if (!p)
			return (0);
		p[0] = 48;
		p[1] = '\0';
	}
	if (nb == -2147483648)
		p = minint(p, nb, n, count);
	else if (nb > 0)
		p = ft_pos(p, nb, n, count);
	else if (nb < 0)
		p = ft_negatif(p, nb, n, count);
	return (p);
}
