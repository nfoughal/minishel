/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:40:29 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:24:34 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envcmd(t_env *my_vrbs)
{
	if (!my_vrbs)
		return (-1);
	if (g_global.envflag == 0)
	{
		while (my_vrbs)
		{
			printf("%s", my_vrbs->key);
			if (my_vrbs->value)
				printf("=%s\n", my_vrbs->value);
			my_vrbs = my_vrbs->next;
		}
	}
	else if (g_global.envflag == 1)
	{
		while (my_vrbs)
		{
			if (ft_strcmp(my_vrbs->key, "PATH") != 0 && my_vrbs->value)
				printf("%s", my_vrbs->key);
			if (my_vrbs->value && ft_strcmp(my_vrbs->key, "PATH") != 0)
				printf("=%s\n", my_vrbs->value);
			my_vrbs = my_vrbs->next;
		}
	}
	g_global.exit_status = 0;
	return (1);
}

int	alt_unset(t_env *tmp1_env, t_env *tmp2_env, char *var)
{
	while (tmp2_env)
	{
		if (ft_strcmp(tmp2_env->key, var) == 0)
		{
			tmp1_env->next = tmp2_env->next;
			free(tmp2_env->key);
			free(tmp2_env->value);
			free(tmp2_env);
			g_global.exit_status = 0;
			return (1);
		}
		tmp1_env = tmp2_env;
		tmp2_env = tmp2_env->next;
	}
	return (0);
}

int	unsetcmd(t_env **env, t_arg *var)
{
	t_env	*tmp1_env;
	t_env	*tmp2_env;

	if (!var || !env)
		return (-1);
	while (var)
	{
		if (verified_unset(var->data))
			return (1);
		tmp1_env = *env;
		if (ft_strcmp((*env)->key, var->data) == 0)
		{
			g_global.exit_status = 0;
			(*env) = (*env)->next;
			free(tmp1_env->key);
			free(tmp1_env->value);
			free(tmp1_env);
			return (1);
		}
		tmp2_env = (*env)->next;
		if (alt_unset(tmp1_env, tmp2_env, var->data))
			return (1);
		var = var->next;
	}
	return (1);
}

int	unset_more(t_env **env, t_arg *var)
{
	while (var)
	{
		unsetcmd(env, var);
		var = var->next;
	}
	return (-1);
}

int	exitcmd(t_arg *stat)
{
	ft_putstr_fd("exit\n", 2);
	if (stat)
	{
		if (!ft_isumber(stat->data))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(stat->data, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else if (stat->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_global.exit_status = 1;
			return (-1);
		}
		else
		{
			g_global.exit_status = ft_atoi(stat->data);
			exit(g_global.exit_status);
		}
	}
	exit(0);
}
