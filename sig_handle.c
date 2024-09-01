/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 08:13:22 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:53:51 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_sigint(int capt)
{
	if (capt == SIGINT && g_global.read_stat == READING)
	{
		g_global.exit_status = 1;
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (capt == SIGINT && g_global.read_stat == HERE_DOC)
	{
		g_global.true_herdoc = 1;
		write(1, "\n", 1);
		close(0);
		g_global.read_stat = 963;
	}
	else if (capt == SIGINT && g_global.read_stat == EXECUTION)
	{
	}
}

void	do_sigquit(int capt)
{
	if (capt == SIGQUIT)
		;
}

int	sig_handling(void)
{
	void	*ret1;
	void	*ret2;

	ret1 = signal(SIGINT, do_sigint);
	ret2 = signal(SIGQUIT, do_sigquit);
	if (ret1 == SIG_ERR || ret2 == SIG_ERR)
		return (ft_putstr_fd("Error in signals ...", 2), exit(1), 1);
	return (0);
}
