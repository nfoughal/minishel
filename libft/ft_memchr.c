/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:20:56 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/29 13:35:40 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;
	unsigned char	j;

	p = (unsigned char *) s;
	j = (unsigned char) c;
	i = 0;
	while (n)
	{
		if (*p == j)
			return (p);
		n--;
		p++;
	}
	return (0);
}
