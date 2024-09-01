/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:11:13 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 21:55:47 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_nullenv(t_env **list_env)
{
	char	cwd[1000];

	g_global.envflag = 1;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_lstadd_back_env(list_env, ft_lstnew_env(ft_strdup("PWD"),
				ft_strdup(cwd)));
	else
		perror("getcwd() error");
	ft_lstadd_back_env(list_env, ft_lstnew_env(ft_strdup("SHLVL"),
			ft_strdup("1")));
	ft_lstadd_back_env(list_env, ft_lstnew_env(ft_strdup("PATH"),
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	ft_lstadd_back_env(list_env, ft_lstnew_env(ft_strdup("_"),
			ft_strdup("/usr/bin/env")));
	return ;
}

void	fill_env(char **env, t_env **list_env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (!env || !(*env))
		fill_nullenv(list_env);
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		k = j + 1;
		ft_lstadd_back_env(list_env,
			ft_lstnew_env(ft_substr(env[i], 0, j), ft_strdup(env[i] + k)));
		i++;
	}
}
