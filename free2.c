/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:03 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/11 01:18:11 by nfoughal         ###   ########.fr       */
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

void	free_main(char *line, t_list *list, t_env *list_env, t_myshell *c_list)
{
	free_list_joiner();
	free(line);
	free_list(list);
	free_env_list(list_env);
	free_shell(c_list);
}
