/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:41:58 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 22:08:01 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_help(t_myshell *c_list, t_env **list_env, int out, int in)
{
	int	id;

	id = 0;
	g_global.read_stat = EXECUTION;
	if (c_list)
	{
		if (c_list->next == NULL)
			id = one_cmd(c_list, list_env, out, in);
		else
			id = more_cmds(c_list, (*list_env));
		while (wait(NULL) != -1)
			;
		if (errno != ECHILD)
			perror("Error in wait");
	}
	return (id);
}

void	init_main(t_list **list, t_myshell **c_list, int *in, int *out)
{
	(*c_list) = NULL;
	(*list) = NULL;
	dup2((*out), 1);
	dup2((*in), 0);
}

int	loop_inf(t_all_list *all)
{
	while (1)
	{
		g_global.read_stat = READING;
		init_main(&all->list, &all->c_list, &all->in, &all->out);
		g_global.in_cltc = all->in;
		all->line = readline("myshell> ");
		if (!all->line)
			return (write(1, "\n", 1), g_global.exit_status = 0);
		if (ft_strcmp("", all->line) != 0)
			add_history(all->line);
		fill_list(all->line, &all->list);
		if (check_error(all->list, all->line) != 0)
			continue ;
		fill_clean_list(all->list, &all->c_list, all->list_env);
		if (isatty(0) == 0)
		{
			free_main(all->line, all->list, all->c_list);
			continue ;
		}
		main_help(all->c_list, &all->list_env, all->out, all->in);
		free_main(all->line, all->list, all->c_list);
	}
	free_env_list(all->list_env);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_all_list	all;

	(void)av;
	if (ac == 1)
	{
		all.list_env = NULL;
		g_global.read_stat = EXECUTION;
		fill_env(env, &all.list_env);
		add_status(&all.list_env);
		sig_handling();
		all.out = dup(1);
		all.in = dup(0);
		all.i = loop_inf(&all);
		return (all.i);
	}
	else
		ft_putstr_fd("Minishell: : nº of args must be one\n", 2);
	return (1);
}
