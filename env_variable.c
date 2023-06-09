/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:11:13 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/03 03:43:11 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_env(char **env, t_env **list_env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
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
