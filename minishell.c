/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:46:39 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 21:40:53 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_outfile_list(t_outfile **list_outfile,
t_list **list, t_env *list_env)
{
	t_outfile	*new;
	t_outfile	*new2;

	if ((*list)->trag == TOKEN_REDIRECTION)
	{
		(*list) = (*list)->next;
		new = ft_lstnew_outfile(get_string(list, list_env, 0));
		ft_lstadd_back_outfile(list_outfile, new);
		new->flag = TOKEN_DOUBLE_RED;
		new->number = g_global.i++;
	}
	else
	{
		(*list) = (*list)->next;
		new2 = ft_lstnew_outfile(get_string(list, list_env, 0));
		ft_lstadd_back_outfile(list_outfile, new2);
		new2->number = g_global.i++;
	}
}

void	fill_file(int file, char *dill, t_env *env)
{
	char	*line;

	g_global.read_stat = HERE_DOC;
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(dill, line, (ft_strlen(dill) + 1)) == 0)
		{
			free(line);
			break ;
		}
		if (g_global.dill_flag == 0)
			line = get_current_path(env, line, 0, 0);
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
		line = readline("> ");
	}
	g_global.read_stat = READING;
}

void	fill_herdoc_file(t_list **list, t_infile **list_infile,
t_env *list_env, int i)
{
	char	*dill;
	char	*itoa_s;
	char	*join_s;
	int		file;

	(*list) = (*list)->next;
	dill = get_string(list, list_env, 1);
	i = 100;
	itoa_s = ft_itoa(i);
	join_s = ft_strjoin("/tmp/herdoc", itoa_s);
	while (access(join_s, F_OK) == 0)
	{
		i++;
		free(itoa_s);
		free(join_s);
		itoa_s = ft_itoa(i);
		join_s = ft_strjoin("/tmp/herdoc", itoa_s);
	}
	file = open(join_s, O_CREAT | O_WRONLY, 0777);
	if (file == -1)
		return ;
	fill_file(file, dill, list_env);
	ft_lstadd_back_infile(list_infile, ft_lstnew_infile(join_s));
	free(itoa_s);
	free(dill);
}

void	fill_myshell(t_list **list, t_all_list *pp, t_myshell **c_list)
{
	ft_lstadd_back_myshell(c_list,
		ft_lstnew_myshell(pp->list_arg, pp->list_infile, pp->list_outfile));
	(pp->list_arg) = NULL;
	(pp->list_infile) = NULL;
	(pp->list_outfile) = NULL;
	if (*list)
		(*list) = (*list)->next;
}

void	fill_clean_list(t_list *list, t_myshell **c_list, t_env *list_env)
{
	t_all_list	pp;

	pp.list_arg = NULL;
	pp.list_infile = NULL;
	pp.list_outfile = NULL;
	while (list)
	{
		if (list->next && (list->trag == TOKEN_GREATER_THAN
				|| list->trag == TOKEN_REDIRECTION))
			fill_outfile_list(&pp.list_outfile, &list, list_env);
		else if (list->next && (list->trag == TOKEN_LESS_THAN))
		{
			list = list->next;
			pp.new1 = ft_lstnew_infile(get_string(&list, list_env, 0));
			ft_lstadd_back_infile(&pp.list_infile, pp.new1);
			pp.new1->number = g_global.i++;
		}
		else if (list->next && (list->trag == TOKEN_HERDOC))
			fill_herdoc_file(&list, &pp.list_infile, list_env, 0);
		else
			ft_lstadd_back_args(&pp.list_arg,
				ft_lstnew_args(get_string(&list, list_env, 0)));
		if (list == NULL || list->trag == TOKEN_PIPE)
			fill_myshell(&list, &pp, c_list);
	}
}
