/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:00:04 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/29 18:38:16 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	m;
	size_t	n;

	n = ft_strlen(src);
	if (dstsize == 0)
		return (n);
	j = 0;
	m = ft_strlen(dst);
	if (dstsize < m)
		return (n + dstsize);
	while (src[j] != '\0' && (j + m + 1) < dstsize)
	{
		dst[m + j] = src[j];
		j++;
	}
	dst[m + j] = '\0';
	return (n + m);
}
