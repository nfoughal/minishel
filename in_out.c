/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 00:36:39 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:54:36 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output(t_outfile *out, int dupout, int dupin)
{
	int	a;

	if (out->flag == 11)
		a = open(out->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		a = open(out->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(a, 1);
	ft_close(a);
	if (a < 0)
	{
		dup2(dupout, 1);
		dup2(dupin, 0);
		ft_close(dupout);
		g_global.exit_status = 1;
		if (access(out->data, W_OK) == -1)
		{
			printf("minishell: %s: Permission denied\n", out->data);
			return (-1);
		}
		else
			return (printf("minishell: %s: Is a directory\n", out->data), -1);
	}
	return (0);
}

int	handle_input(t_infile *in, int dupin, int dupout)
{
	int	fd;

	fd = open(in->data, O_RDONLY);
	dup2(fd, 0);
	ft_close(fd);
	if (fd == -1)
	{
		dup2(dupout, 1);
		dup2(dupin, 0);
		ft_close(dupin);
		g_global.exit_status = 1;
		if (access(in->data, W_OK) == 0)
		{
			printf("Minishell: %s: Permission denied\n", in->data);
			return (-1);
		}
		else
		{
			printf("Minishell: %s: No such file or directory\n", in->data);
			return (-1);
		}
	}
	return (0);
}
