/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:41:58 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/03 17:48:07 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_next(t_list *tokens)
{
	t_list	*list;

	list = tokens;
	if (!tokens->next)
		return (1);
	else if (tokens->next->trag != TOKEN_WORD
		&& tokens->next->trag != TOKEN_DOUBLE_OUTE
		&& tokens->next->trag != TOKEN_SINGLE_OUTE)
		return (1);
	return (0);
}

int	token_loop(t_list *tokens, char *line, int *db_q, int *sb_q)
{
	t_list	*list;

	list = tokens;
	while (tokens)
	{
		if (tokens->trag == TOKEN_GREATER_THAN
			|| tokens->trag == TOKEN_LESS_THAN
			|| tokens->trag == TOKEN_HERDOC
			|| tokens->trag == TOKEN_REDIRECTION)
		{
			if (check_next(tokens))
			{
				free_list(list);
				free(line);
				return (1);
			}
		}
		if (tokens->trag == TOKEN_DOUBLE_OUTE)
			(*db_q)++;
		if (tokens->trag == TOKEN_SINGLE_OUTE)
			(*sb_q)++;
		tokens = tokens->next;
	}
	return (0);
}

int	check_error(t_list *tokens, char *line)
{
	int	db_q;
	int	sb_q;

	db_q = 0;
	sb_q = 0;
	if (ft_lstsize(tokens) == 0)
		return (0);
	if (tokens->trag == TOKEN_PIPE)
	{
		free_list(tokens);
		free(line);
		return (printf("Synatx Error\n"));
	}
	if (token_loop(tokens, line, &db_q, &sb_q))
		return (printf("Synatx Error\n"));
	if (sb_q % 2 != 0 || db_q % 2 != 0)
	{
		free_list(tokens);
		free(line);
		return (printf("Synatx Error\n"));
	}
	return (0);
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
		add_history(line);
		fill_list(line, &list);
		if (check_error(list, line) != 0)
			continue ;
		fill_env(env, &list_env);
		fill_clean_list(list, &c_list, list_env);
		free(line);
		free_list(list);
		free_env_list(list_env);
		free_shell(c_list);
	}
	return (0);
}
