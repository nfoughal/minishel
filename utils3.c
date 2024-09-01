/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 02:31:26 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:48:39 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1)
		return (0);
	if (!s2)
		s2 = ft_strdup("");
	p = (char *) malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	i = 0;
	j = 0;
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	free((char *)s1);
	return (p);
}

void	ft_close(int fd)
{
	if (fd != 0 && fd != 1)
		close(fd);
}

void	ft_perror(char *str, char *error)
{
	g_global.exit_status = 126;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	print_exit_error(int status)
{
	if (status == SIGABRT + 128)
		ft_putstr_fd("Abort trap: 6\n", 2);
	else if (status == SIGSEGV + 128)
		ft_putstr_fd("Segmentation fault: 11\n", 2);
	else if (status == SIGHUP + 128)
		ft_putstr_fd("hangup: 1\n", 2);
	else if (status == SIGQUIT + 128)
		ft_putstr_fd("Quit: 3\n", 2);
	else if (status == SIGILL + 128)
		ft_putstr_fd("illegal instruction: 4\n", 2);
	else if (status == SIGTRAP + 128)
		ft_putstr_fd("trace trap: 5\n", 2);
	else if (status == SIGEMT + 128)
		ft_putstr_fd("EMT instruction: 7\n", 2);
	else if (status == SIGFPE + 128)
		ft_putstr_fd("floating point exception: 8\n", 2);
	else if (status == SIGKILL + 128)
		ft_putstr_fd("kill: 9\n", 2);
	else if (status == SIGBUS + 128)
		ft_putstr_fd("bus error: 10\n", 2);
	else
		return ;
}

int	get_exit_status(int prcs_id)
{
	int	x;

	waitpid(prcs_id, &g_global.exit_status, 0);
	if (WIFSIGNALED(g_global.exit_status))
	{
		x = WTERMSIG(g_global.exit_status) + 128;
		print_exit_error(x);
		return (x);
	}
	return (WEXITSTATUS(g_global.exit_status));
}
