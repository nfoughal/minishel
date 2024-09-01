/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:11:54 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/29 13:37:58 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t					i;
	size_t					k;
	size_t					j;

	i = 0;
	if (!haystack && len == 0)
		return (0);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		k = 0;
		j = 0;
		while ((needle[j] == haystack[j]) && (i + k++ < len))
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack);
		}
		haystack++;
		i++;
	}
	return (NULL);
}
