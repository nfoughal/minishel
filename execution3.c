/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 02:33:38 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 17:37:42 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	one_cmd(t_myshell *c_list, t_env **list_env, int out, int in)
{
	int	k;
	int	id;

	g_global.cerr = -2;
	id = 0;
	if (c_list->infile || c_list->outfile)
		if (in_out_handling(c_list->infile, c_list->outfile, in, out) == -1)
			return (1);
	k = is_built_incmd(c_list, list_env);
	if (k == -1)
		id = is_execuve_cmd(c_list, list_env, -2, -2);
	return (id);
}

int	more_cmds(t_myshell *c_list, t_env *list_env)
{
	int	in;
	int	out;
	int	ppe[2];
	int	id;

	while (c_list)
	{
		if (pipe(ppe) == -1)
			ft_putstr_fd("Error in Pipe\n", 2);
		out = ppe[1];
		g_global.cerr = ppe[0];
		if (!c_list->next)
		{
			ft_close(out);
			ft_close(ppe[0]);
			out = 1;
		}
		id = is_execuve_cmd(c_list, &list_env, in, out);
		ft_close(out);
		ft_close(in);
		in = ppe[0];
		c_list = c_list->next;
	}
	ft_close(in);
	return (id);
}

int	check_is_buildin(t_arg *args)
{
	if (ft_strcmp(args->data, "pwd") == 0)
		return (1);
	else if (ft_strcmp(args->data, "cd") == 0)
		return (1);
	else if (ft_strcmp(args->data, "echo") == 0)
		return (1);
	else if (ft_strcmp(args->data, "unset") == 0)
		return (1);
	else if (ft_strcmp(args->data, "env") == 0)
		return (1);
	else if (ft_strcmp(args->data, "exit") == 0)
		return (1);
	else if (ft_strcmp(args->data, "export") == 0)
		return (1);
	else
		return (0);
}

void	add_status(t_env **list)
{
	t_env	*tmp;

	tmp = NULL;
	g_global.exit_status = 0;
	g_global.env = *list;
}
