/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:15:39 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/02 16:15:55 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*p;

	p = (t_env *)malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->key = key;
	p->value = value;
	p->next = NULL;
	return (p);
}
