/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:27:47 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 21:52:37 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p && p->next != NULL)
			p = p->next;
		p->next = new;
	}
}
