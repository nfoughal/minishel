/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_support.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:46:23 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/11 21:48:50 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herdoc_check(char *line, t_list **list)
{
	char	*p;
	t_list	*new;

	if ((ft_strncmp(line, ">>", 2) == 0) || (ft_strncmp(line, "<<", 2) == 0))
	{
		p = malloc(sizeof(char) * 3);
		p[0] = *line;
		p[1] = *line;
		p[2] = '\0';
		new = ft_lstnew(p);
		ft_lstadd_back(list, new);
		if (*line == '<')
		{
			new->trag = TOKEN_HERDOC;
			return (2);
		}
		if (*line == '>')
		{
			new->trag = TOKEN_REDIRECTION;
			return (1);
		}
	}
	return (0);
}

int	ft_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '>' && line[i] != '<'
		&& line[i] != '\"' && line[i] != '\'' && line[i] != '|' && line[i])
			i++;
	return (i);
}

char	*str_dup(char *line)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = ft_line(line);
	if (len == 0)
		return (NULL);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = *line;
		i++;
		line++;
	}
	p[i] = '\0';
	return (p);
}

int	between_q_count(char **line, int flag)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (flag == 1)
	{
		while ((*line)[i] && ((*line)[i] != '\"'))
		{
			i++;
			count++;
		}
	}
	else
	{
		while ((*line)[i] && ((*line)[i] != '\''))
		{
			i++;
			count++;
		}
	}
	return (count);
}

void	fill_cout(char **line, t_list **list, int j)
{
	char	*p;
	t_list	*new;

	p = malloc(sizeof(char) * 2);
	if (!p)
		return ;
	p[0] = **line;
	p[1] = '\0';
	new = ft_lstnew(p);
	ft_lstadd_back(list, new);
	if (**line == '\"')
		new->trag = TOKEN_DOUBLE_OUTE;
	else
		new->trag = TOKEN_SINGLE_OUTE;
	(*line)++;
	if (j == 1)
	{
		if (**line == ' ' || **line == '\t')
		new->flag = TOKEN_ESPACE;
	}
}
