/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:13:36 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/02 16:15:35 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_lstadd_back_args(t_arg **lst, t_arg *new)
{
	t_arg	*p;

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

t_arg	*ft_lstnew_args(char *data)
{
	t_arg	*p;

	p = (t_arg *)malloc(sizeof(t_arg));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back_outfile(t_outfile **lst, t_outfile *new)
{
	t_outfile	*p;

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

t_outfile	*ft_lstnew_outfile(char *data)
{
	t_outfile	*p;

	p = (t_outfile *)malloc(sizeof(t_outfile));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}
