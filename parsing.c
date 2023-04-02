/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:23:02 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/01 17:50:57 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char **line, t_list **list)
{
	t_list	*new;
	char	*s;
	int		i;

	i = 0;
	fill_cout(line, list, 0);
	i = between_q_count(line);
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return ;
	i = 0;
	while ((**line) && (**line != '\"' && **line != '\''))
	{
		s[i++] = **line;
		(*line)++;
	}
	s[i] = '\0';
	new = ft_lstnew(s);
	ft_lstadd_back(list, new);
	if (**line == '\"')
	new->trag = TOKEN_WORD;
	if (**line == '\'')
		new->trag = TOKEN_WORD_SINGLE_COUT;
	if (**line == '\"' || **line == '\'')
		fill_cout(line, list, 1);
}

void	list_dup(char *line, t_list **list, int *ifdup, t_list **new1)
{
	char	*dup;

	dup = str_dup(line);
	if (dup != NULL)
	{
		(*new1) = ft_lstnew(dup);
		ft_lstadd_back(list, (*new1));
		(*new1)->trag = TOKEN_WORD;
		*ifdup = 1;
	}
}

void	if_herdoc_valid(char **line, t_list **list, int *flag)
{
	int	cheker;

	cheker = herdoc_check(*line, list);
	if (cheker != 0)
	{
		(*line) += 2;
		*flag = 1;
	}
}

void	fill_tokens(t_list **list, char **line)
{
	t_list	*new;
	char	*p;

	p = malloc(sizeof(char) * 2);
	if (!p)
		return ;
	p[0] = **line;
	p[1] = '\0';
	new = ft_lstnew(p);
	ft_lstadd_back(list, new);
	if (**line == '|')
		new->trag = TOKEN_PIPE;
	else if (**line == '>')
		new->trag = TOKEN_GREATER_THAN;
	else if (**line == '<')
		new->trag = TOKEN_LESS_THAN;
	(*line)++;
}

void	skeep_spaces(char **line, t_list **new1, int *ifdup)
{
	while (**line == ' ')
	{
		(*line)++;
		if (*ifdup == 1)
		{
			(*new1)->flag = TOKEN_ESPACE;
			(*ifdup) = 0;
		}
	}
}
