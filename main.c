/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:41:58 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/11 02:16:45 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_g_vb	g_test;

void	free_list_joiner(void)
{
	int		b;
	t_list	*tmp;

	b = 0;
	while (g_test.freeable && b < g_test.n_iterations)
	{
		b++;
		tmp = g_test.freeable->next;
		free(g_test.freeable->data);
		free(g_test.freeable);
		g_test.freeable = tmp;
	}
	g_test.n_iterations = 0;
	g_test.freeable = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_list		*list;
	t_myshell	*c_list;
	t_env		*list_env;
	char		*line;

	(void)ac;
	(void)av;
	while (1)
	{
		list = NULL;
		list_env = NULL;
		c_list = NULL;
		line = readline("myshell> ");
		if (!line)
			return (0);
		add_history(line);
		fill_list(line, &list);
		if (check_error(list, line) != 0)
			continue ;
		fill_env(env, &list_env);
		fill_clean_list(list, &c_list, list_env);
		free_main(line, list, list_env, c_list);
	}
	return (0);
}
