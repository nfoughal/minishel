/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:47:08 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:49:10 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flagged(t_list **list)
{
	return ((*list) && (*list)->trag != 1 && (*list)->flag != 10
		&& (*list)->trag != 6 && (*list)->trag != TOKEN_LESS_THAN
		&& (*list)->trag != TOKEN_PIPE && (*list)->trag != TOKEN_HERDOC
		&& (*list)->trag != TOKEN_REDIRECTION);
}

int	verified_unset(char *str)
{
	if (!ft_isalpha(str[0]) || is_verified(str) != 1)
	{
		g_global.exit_status = 1;
		ft_putstr_fd("minishell: unset: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (1);
	}
	return (0);
}

int	exportcmd(t_env **env, t_arg *args)
{
	if (!(env))
		return (-1);
	if (!args)
		return (only_export(env));
	while (args)
	{
		exportcmd2(env, args);
		args = args->next;
	}
	return (-1);
}

void	ft_close2(int fd1, int fd2, int fd3)
{
	if (fd1 != 0 && fd1 != 1)
		close(fd1);
	if (fd2 != 0 && fd2 != 1)
		close(fd2);
	if (fd3 != 0 && fd3 != 1)
		close(fd3);
}

void	dis_fun(void)
{
	write(2, "minishell: : command not found\n", 32);
	return ;
}
