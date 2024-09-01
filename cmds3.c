/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:42:29 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:07:46 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_export(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	g_global.exit_status = 0;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('\"', 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	return (1);
}

int	change_env(t_env **env, char *attr, char *old_key)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(old_key, (tmp)->key) == 0)
		{
			tmp->value = ft_strjoin(tmp->value, attr);
			free(attr);
			return (1);
		}
		tmp = tmp->next;
	}
	return (i);
}

int	is_verified(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9' && i != 0)
			&& !(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] == '=' || str[i] == '+' || str[i] == '_' ))
			return (0);
		i++;
	}
	return (1);
}

char	*get_newkey(char *key)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			len = ft_strlen(key) - i;
		i++;
	}
	new = malloc(len + 1);
	new[len] = '\0';
	i = (i - len) + 1;
	len = 0;
	while (key[i])
		new[len++] = key[i++];
	return (new);
}

int	key_notexist(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (0);
		env = env->next;
	}
	return (1);
}
