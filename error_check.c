/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:11:23 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/14 17:45:15 by moouaamm         ###   ########.fr       */
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
	if (tokens->trag == TOKEN_PIPE || ft_lstlast(tokens)->trag == TOKEN_PIPE)
	{
		free_list(tokens);
		free(line);
		return ((g_global.exit_status = 258),
			ft_putstr_fd("Synatx Error\n", 2), 1);
	}
	if (token_loop(tokens, line, &db_q, &sb_q))
		return ((g_global.exit_status = 258),
			ft_putstr_fd("Synatx Error\n", 2), 1);
	if (sb_q % 2 != 0 || db_q % 2 != 0)
	{
		free_list(tokens);
		free(line);
		return ((g_global.exit_status = 258),
			ft_putstr_fd("Synatx Error\n", 2), 1);
	}
	return (0);
}
