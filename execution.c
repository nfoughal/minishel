/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:49:48 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:33:21 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_incmd(t_myshell *c_list, t_env **list_env)
{
	if (c_list->args)
	{
		if (ft_strcmp(c_list->args->data, "pwd") == 0)
			return (pwdcmd(), 1);
		else if (ft_strcmp(c_list->args->data, "cd") == 0)
			return (cdcmd(c_list, *list_env), 1);
		else if (ft_strcmp(c_list->args->data, "env") == 0)
			return (envcmd(*list_env), 1);
		else if (ft_strcmp(c_list->args->data, "export") == 0)
			return (exportcmd(list_env, c_list->args->next), 1);
		else if (ft_strcmp(c_list->args->data, "unset") == 0)
			return (unset_more(list_env, c_list->args->next), 1);
		else if (ft_strcmp(c_list->args->data, "exit") == 0)
			return (exitcmd(c_list->args->next), 1);
		if (ft_strcmp(c_list->args->data, "echo") == 0)
			return (echocmd(c_list->args->next, *list_env), 1);
	}
	return (-1);
}

char	**env_to_str(t_env *list)
{
	t_env	*tmp;
	char	**env;
	char	*str;
	int		i;

	i = 0;
	tmp = list;
	while (tmp && ++i)
		tmp = tmp->next;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	env[i] = NULL;
	i = 0;
	while (list)
	{
		str = ft_strjoin(list->key, "=");
		env[i] = ft_strjoin(str, list->value);
		free(str);
		list = list->next;
		i++;
	}
	return (env);
}

int	child_process(t_myshell *c_list, t_env *list_env)
{
	char	**argm;
	char	**pts;
	char	**env;
	char	*trp;

	argm = NULL;
	if (!list_env || !c_list->args)
		exit(g_global.exit_status);
	env = env_to_str(list_env);
	if (c_list->args)
		argm = get_options(c_list->args);
	trp = true_path(list_env);
	pts = ft_split(trp, ':');
	free(trp);
	trp = valid_path(pts, argm[0]);
	if (!trp)
		exit(g_global.exit_status);
	free_fun(pts);
	free_shell(c_list);
	free_env_list(list_env);
	execve(trp, argm, env);
	g_global.exit_status = 127;
	write(2, "minishellnn: ", 12);
	ft_putstr_fd(argm[0], 2);
	return (perror(""), free(trp), free_fun(argm), free_fun(env), exit(1), 1);
}

int	in_out_handling(t_infile *infile, t_outfile *outfile, int in, int out)
{
	int	i;

	i = -1;
	while (++i <= g_global.i)
	{
		if ((infile && outfile && (infile->number < outfile->number)))
		{
			if (handle_input((infile), in, out))
				return (-1);
			(infile) = (infile)->next;
		}
		else if (outfile)
		{
			if (handle_output((outfile), out, in))
				return (-1);
			(outfile) = (outfile)->next;
		}
		else if (infile)
		{
			if (handle_input((infile), in, out))
				return (-1);
			(infile) = (infile)->next;
		}
	}
	return (0);
}

int	is_execuve_cmd(t_myshell *c_list, t_env **list_env, int in, int out)
{
	int		k;
	pid_t	d;

	d = fork();
	if (d < 0)
		return (ft_putstr_fd("Error in fork", 2), 1);
	if (d == 0)
	{
		if (g_global.cerr > 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			ft_close2(in, out, g_global.cerr);
		}
		if (c_list->infile || c_list->outfile)
			if (in_out_handling(c_list->infile, c_list->outfile, in, out))
				exit (1);
		k = is_built_incmd(c_list, list_env);
		if (k == -1)
			child_process(c_list, *list_env);
		exit(g_global.exit_status);
	}
	if (c_list->next == NULL)
		g_global.exit_status = get_exit_status(d);
	return (g_global.exit_status);
}
