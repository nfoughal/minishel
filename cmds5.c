/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 22:17:28 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:26:31 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cdcmd(t_myshell *shell, t_env *envi)
{
	if (!shell->args || !envi)
		return (1);
	if (shell->args->next == NULL)
	{
		while (ft_strcmp(envi->key, "HOME") != 0)
			envi = envi->next;
		ft_lstadd_back_args(&shell->args,
			ft_lstnew_args(ft_strdup(envi->value)));
	}
	if (ft_strcmp(shell->args->next->data, "-") == 0)
	{
		free(shell->args->next->data);
		while (ft_strcmp(envi->key, "OLDPWD") != 0)
			envi = envi->next;
		shell->args->next->data = ft_strdup(envi->value);
		printf("%s\n", shell->args->next->data);
	}
	if (chdir((const char *)shell->args->next->data) != 0)
	{
		g_global.exit_status = 1;
		return (perror("chdir"), 1);
	}
	return (-1);
}

void	there_is_equal(t_arg **args, int flag, int i, t_env **env)
{
	char	*new_key;
	char	*new_value;

	new_value = malloc((ft_strlen((*args)->data + i)));
	if (!new_value)
		exit(1);
	ft_strlcpy(new_value, ((*args)->data + i + 1),
		ft_strlen(((*args)->data + i)));
	ft_get_newkey(&new_key, (*args)->data, i, flag);
	add_env_var(new_key, new_value, env, flag);
	free(new_key);
	free(new_value);
}

int	alt_export(t_env **env, t_arg *args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (args->data[i] && args->data[i] != '='
		&& !(args->data[i] == '+' && args->data[i + 1] == '='))
			i++;
	if (args->data[i] == '+')
	{
		flag = 1;
		i++;
	}
	if (args->data[i] == '=')
		there_is_equal(&args, flag, i, env);
	else
		_null_value(args->data, env);
	args = args->next;
	return (1);
}

int	ft_isumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i] && str[i + 1])
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	if (ft_atoi(str) > LLONG_MAX)
		return (0);
	return (1);
}
