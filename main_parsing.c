/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:49:40 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/11 02:13:38 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_list(char *line, t_list **list)
{
	int		flag;
	t_list	*new1;
	int		ifdup;

	ifdup = 0;
	while (*line == ' ' || *line == '\t')
		line++;
	while (*line)
	{
		flag = 0;
		list_dup(line, list, &ifdup, &new1);
		while (*line != ' ' && *line != '>' && *line != '<' && *line
			!= '\"' && *line != '\'' && *line != '|' && *line && *line != '\t')
			line++;
		if (*line == '\"' || *line == '\'')
		{
			check_quotes(&line, list);
			ifdup = 0;
		}
		if (*line == '>' || *line == '<')
			if_herdoc_valid(&line, list, &flag);
		if ((*line == '>' || *line == '<' || *line == '|') && (flag == 0))
			fill_tokens(list, &line);
		skeep_spaces(&line, &new1, &ifdup);
	}
}
