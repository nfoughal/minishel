/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:43:17 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:25:30 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_newkey(char **key, char *str, int i, int flag)
{
	if (flag)
	{
		*(key) = malloc((ft_strlen(str) - ft_strlen(str + i)));
		if (!*(key))
			exit(1);
		ft_strlcpy(*(key), str, ((ft_strlen(str) - ft_strlen(str + i))));
	}
	else
	{
		*(key) = malloc((ft_strlen(str) - ft_strlen(str + i) + 1));
		if (!*(key))
			exit(1);
		ft_strlcpy(*(key), str, ((ft_strlen(str) - ft_strlen(str + i) + 1)));
	}
}

void	add_node_env(t_env **env, char *value, char *key)
{
	t_env	*new;
	t_env	*tmp;

	tmp = *env;
	new = malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->value = ft_strdup(value);
	new->key = ft_strdup(key);
	new->next = NULL;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_env_var(char *new_key, char *new_value, t_env **env, int flag)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && ft_strcmp(new_key, tmp->key))
		tmp = tmp->next;
	if (tmp && !ft_strcmp(new_key, tmp->key))
	{
		if (new_value && flag == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
		}
		else if (new_value && flag == 1)
		{
			tmp->value = ft_strjoin2(tmp->value, new_value);
		}
	}
	else
		add_node_env(env, new_value, new_key);
}

void	_null_value(char *attr, t_env **env)
{
	t_env	*tmp_env;

	tmp_env = *env;
	while (tmp_env && ft_strncmp(tmp_env->key, attr, ft_strlen((*env)->key)))
		tmp_env = tmp_env->next;
	if (tmp_env)
		return ;
	ft_lstadd_back_env(env, ft_lstnew_env(ft_strdup(attr), NULL));
}

int	exportcmd2(t_env **env, t_arg *args)
{
	if (!ft_isalpha(args->data[0]) || is_verified(args->data) != 1)
	{
		g_global.exit_status = 1;
		ft_putstr_fd("minishell: export: `", 1);
		ft_putstr_fd(args->data, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		g_global.exit_status = 1;
		return (1);
	}
	else
		alt_export(env, args);
	return (1);
}
