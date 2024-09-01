/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:47:31 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 21:45:27 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_string_cout(t_list **list, t_env *list_env,
char **string, char *str_tmp)
{
	char	*path;
	int		i;
	char	*tmp_str;

	tmp_str = get_current_path(list_env, ft_strdup((*list)->data),
			i = 0, (*list)->trag);
	if ((*list)->double_cout != TOKEN_WORD_DOUBLE_COUT
		&& ft_strchr((*list)->data, '$')
		&& (ft_strcmp(tmp_str, "") != 0))
	{
		list_joine(list, list_env);
		free(tmp_str);
		return (0);
	}
	else
	{
		path = get_current_path(list_env, ft_strdup((*list)->data),
				i = 0, (*list)->trag);
		(*string) = ft_strjoin((*string), path);
		free(path);
		free(str_tmp);
		free(tmp_str);
		return (1);
	}
	free(tmp_str);
}

void	check_if_string_cout_flag(t_list **list, t_env *list_env,
char **string, char *str_tmp)
{
	char	*path;
	int		i;
	char	*str;

	str = get_current_path(list_env, ft_strdup((*list)->data),
			i = 0, (*list)->trag);
	if ((*list)->double_cout != TOKEN_WORD_DOUBLE_COUT
		&& ft_strchr((*list)->data, '$')
		&& (ft_strcmp(str, "") != 0))
	{
		list_joine(list, list_env);
		(*string) = ft_strjoin((*string), (*list)->data);
		free(str_tmp);
	}
	else
	{
		path = get_current_path(list_env, ft_strdup((*list)->data),
				i = 0, (*list)->trag);
		(*string) = ft_strjoin((*string), path);
		free(path);
		free(str_tmp);
	}
	free(str);
}

char	*string_re(t_list **list, t_env *list_env,
int herdoc_flag, char *string)
{
	char	*str_tmp;

	str_tmp = string;
	if ((*list)->trag == TOKEN_WORD_SINGLE_COUT)
	{
		string = ft_strjoin(string, (*list)->data);
		free(str_tmp);
	}
	else if ((*list)->trag == TOKEN_WORD && herdoc_flag != 1)
	{
		if (check_if_string_cout(list, list_env, &string, str_tmp) == 0)
			return (NULL);
	}
	else if ((*list)->trag == TOKEN_WORD && herdoc_flag == 1)
	{
		string = ft_strjoin(string, (*list)->data);
		free(str_tmp);
	}
		(*list) = (*list)->next;
	return (string);
}

char	*part_2(t_list **list, char *string, int herdoc_flag, t_env *list_env)
{
	char	*str_tmp;

	str_tmp = string;
	if (herdoc_flag != 1)
		check_if_string_cout_flag(list, list_env, &string, str_tmp);
	else
	{
		string = ft_strjoin(string, (*list)->data);
		free(str_tmp);
	}
	(*list) = (*list)->next;
	return (string);
}

char	*get_string(t_list **list, t_env *list_env, int herdoc_flag)
{
	t_all_list	pp;

	g_global.dill_flag = 0;
	pp.string = ft_strdup("");
	while (is_flagged(list))
	{
		if (((*list)->trag == 2) || ((*list)->trag == 3))
			g_global.dill_flag = 1;
		pp.ret = string_re(list, list_env, herdoc_flag, pp.string);
		if (!pp.ret)
			continue ;
		else
		{
			pp.string = pp.ret;
			if ((*list) == NULL)
				return (pp.string);
		}
	}
	if ((*list) && (*list)->flag == TOKEN_ESPACE && ((*list)->trag == TOKEN_WORD
			|| (*list)->trag == TOKEN_WORD_SINGLE_COUT))
		pp.string = part_2(list, pp.string, herdoc_flag, list_env);
	if ((*list) && ((*list)->trag == 2 || (*list)->trag == 3))
		(*list) = (*list)->next;
	return (pp.string);
}
