/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:06:05 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/29 13:38:02 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	m;
	int		l;

	p = (char *)s;
	m = (char)c;
	l = ft_strlen(s);
	while (l >= 0)
	{
		if (p[l] == m)
			return (p + l);
		l--;
	}
	return (0);
}
