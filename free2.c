/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:43:03 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 21:48:13 by moouaamm         ###   ########.fr       */
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

void	free_main(char *line, t_list *list, t_myshell *c_list)
{
	free_list_joiner();
	free(line);
	free_list(list);
	free_shell(c_list);
}

void	free_list_joiner(void)
{
	int		b;
	t_list	*tmp;

	b = 0;
	while (g_global.freeable && b < g_global.n_iterations)
	{
		b++;
		tmp = g_global.freeable->next;
		free(g_global.freeable->data);
		free(g_global.freeable);
		g_global.freeable = tmp;
	}
	g_global.n_iterations = 0;
	g_global.freeable = NULL;
}

int	display_error(char *str)
{
	g_global.exit_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (1);
}
