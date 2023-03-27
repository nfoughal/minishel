/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 22:29:43 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/29 13:35:35 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*node1;
	int		size;

	size = 0;
	node1 = lst;
	while (node1 != NULL)
	{
		node1 = node1->next;
		size++;
	}
	return (size);
}
