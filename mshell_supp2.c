/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_supp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:02:33 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/11 01:24:24 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_g_vb	g_test;

void	free_list_joine(void)
{
	int		b;
	t_list	*tmp;

	b = 0;
	while (g_test.freeable && b < g_test.n_iterations)
	{
		tmp = g_test.freeable->next;
		free(g_test.freeable->data);
		free(g_test.freeable);
		g_test.freeable = tmp;
		b++;
	}
	g_test.n_iterations = 0;
	g_test.freeable = NULL;
}

char	*get_value_from_env(t_env *list_env, char *key)
{
	while (list_env)
	{
		if (ft_strcmp(list_env->key, key) == 0)
			return (list_env->value);
		list_env = list_env->next;
	}
	return ("");
}

char	*get_current_path(t_env *env, char *str, int i, int trag)
{
	char	*result;
	char	*temp;

	(void)i;
	temp = str;
	result = str;
	while (str && ft_strchr(str, '$') && trag != TOKEN_WORD_SINGLE_COUT)
	{
		str = ft_strchr(str, '$');
		if (if_valid_char(str[1]))
		result = data_replace(result, str, env);
		str++;
	}
	if (temp == result)
	result = ft_strdup(result);
	free(temp);
	return (result);
}

void	fill_new_list(t_all_list *pp, char **splited, t_list **list)
{
	while (*splited)
	{
		pp->new = ft_lstnew(*splited);
		pp->new->trag = TOKEN_WORD_SINGLE_COUT;
		pp->new->flag = TOKEN_ESPACE;
		if (!splited[1])
		{
			if ((*list)->flag == TOKEN_ESPACE)
				pp->new->flag = TOKEN_ESPACE;
			else
				pp->new->flag = 0;
		}
		pp->new->double_cout = TOKEN_WORD_DOUBLE_COUT;
		pp->new->out_flag = 0;
		ft_lstadd_back(&pp->new_list, pp->new);
		g_test.n_iterations++;
		if (!g_test.freeable)
			g_test.freeable = pp->new;
		splited++;
	}
}

void	list_joine(t_list **list, t_env *list_env)
{
	t_all_list	pp;
	char		**splited;
	char		*str;
	char		**re;
	int			i;

	free_list_joine();
	g_test.freeable = NULL;
	g_test.n_iterations = 0;
	pp.new_list = NULL;
	str = get_current_path(list_env, ft_strdup((*list)->data),
			i = 0, (*list)->trag);
	splited = ft_split(str, ' ');
	free(str);
	re = splited;
	fill_new_list(&pp, splited, list);
	free(re);
	pp.old_next = (*list)->next;
	*list = pp.new_list;
	if (pp.new_list)
		ft_lstlast(pp.new_list)->next = pp.old_next;
}
