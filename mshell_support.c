/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:47:31 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/03 17:56:21 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_current_path(t_env *list_env, char *str, int i)
{
	int		save;
	char	*f;
	char	*e;
	char	*result;
	char	*value;

	i = 0;
	while (ft_strchr(str, '$'))
	{
		while (str[i] != '$')
		i++;
		f = ft_substr(str, 0, i);
		save = ++i;
		while (str[i++] && (ft_isalnum(str[i++]) || str[i++] == '_'))
			i++;
		e = ft_substr(str + i, 0, ft_strlen(str) - i);
		value = ft_substr(str, save, i - save);
		result = ft_strjoin(f, get_value_from_env(list_env, value));
		free(str);
		str = ft_strjoin(result, e);
		free_all(e, f, value, result);
	}
	return (str);
}

char	*string_re(t_list **list, t_env *list_env,
int herdoc_flag, char *string)
{
	char	*path;
	int		i;
	char	*str_tmp;

	str_tmp = string;
	if ((*list)->trag == TOKEN_WORD_SINGLE_COUT)
	{
		string = ft_strjoin(string, (*list)->data);
		free(str_tmp);
	}
	else if ((*list)->trag == TOKEN_WORD && herdoc_flag != 1)
	{
		path = get_current_path(list_env, ft_strdup((*list)->data), i = 0);
		string = ft_strjoin(string, path);
		free(path);
		free(str_tmp);
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
	char	*path;
	int		i;

	str_tmp = string;
	if (herdoc_flag != 1)
	{
		path = get_current_path(list_env, ft_strdup((*list)->data), i = 0);
		string = ft_strjoin(string, path);
		free(path);
		free(str_tmp);
	}
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
	char	*string;

	string = ft_strdup("");
	while ((*list) && (*list)->trag != 1 && (*list)->flag != 10
		&& (*list)->trag != 6 && (*list)->trag != TOKEN_LESS_THAN
		&& (*list)->trag != TOKEN_PIPE && (*list)->trag != TOKEN_HERDOC
		&& (*list)->trag != TOKEN_REDIRECTION)
		string = string_re(list, list_env, herdoc_flag, string);
	if ((*list) && (*list)->flag == TOKEN_ESPACE && (*list)->trag == TOKEN_WORD)
		string = part_2(list, string, herdoc_flag, list_env);
	if ((*list) && ((*list)->trag == 2 || (*list)->trag == 3))
		(*list) = (*list)->next;
	return (string);
}
