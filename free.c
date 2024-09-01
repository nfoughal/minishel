/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:39:46 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/15 23:56:06 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *list)
{
	t_list	*node;

	node = NULL;
	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void	free_arg_list(t_arg *list)
{
	t_arg	*node;

	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void	free_outfile_list(t_outfile *list)
{
	t_outfile	*node;

	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void	free_infile_list(t_infile *list)
{
	t_infile	*node;

	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void	free_env_list(t_env *list)
{
	t_env	*node;

	while (list)
	{
		node = list->next;
		free(list->key);
		free(list->value);
		list->key = NULL;
		list->value = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}
