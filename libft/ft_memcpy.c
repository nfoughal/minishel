/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:30:01 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/29 13:35:56 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*p;
	unsigned char			*q;
	size_t					i;

	p = (unsigned char *) dst;
	q = (unsigned char *) src;
	i = 0;
	if (!p && !q)
		return (NULL);
	while (i < n)
	{
		p[i] = q[i];
		i++;
	}
	return (p);
}
