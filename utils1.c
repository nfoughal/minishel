/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:14:51 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/02 16:16:09 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_infile(t_infile **lst, t_infile *new)
{
	t_infile	*p;

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

t_infile	*ft_lstnew_infile(char *data)
{
	t_infile	*p;

	p = (t_infile *)malloc(sizeof(t_infile));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back_myshell(t_myshell **lst, t_myshell *new)
{
	t_myshell	*p;

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

t_myshell	*ft_lstnew_myshell(t_arg *args, t_infile *infile,
t_outfile *outfile)
{
	t_myshell	*a;

	a = (t_myshell *)malloc(sizeof(t_myshell));
	if (!a)
		return (NULL);
	a->args = args;
	a->infile = infile;
	a->outfile = outfile;
	a->next = NULL;
	return (a);
}
