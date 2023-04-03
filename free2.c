/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:03 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/03 16:43:59 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_myshell *list)
{
	t_myshell	*node;

	while (list)
	{
		node = list->next;
		free_arg_list(list->args);
		free_infile_list(list->infile);
		free_outfile_list(list->outfile);
		free(list);
		list = node;
	}
}

void	free_all(char *e, char *f, char *value, char *result)
{
	free(e);
	free(f);
	free(value);
	free(result);
}
