/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:16:56 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 21:37:37 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_options(t_arg *options)
{
	t_arg	*tmp_cout;
	char	**args;
	int		i;

	i = 0;
	if (!options)
		return (NULL);
	tmp_cout = options;
	while (tmp_cout)
	{
		i++;
		tmp_cout = tmp_cout->next;
	}
	args = (char **)malloc(sizeof(char *) * (i + 1));
	args[i] = NULL;
	i = 0;
	while (options)
	{
		args[i] = ft_strdup(options->data);
		options = options->next;
		i++;
	}
	return (args);
}

char	*true_path(t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	free_fun(char **str)
{
	int	i;

	i = -1;
	while (++i)
		free(str[i]);
	free(str);
}

char	*check_cmd(char *str)
{
	char		*path;
	char		**args;
	struct stat	data;

	if (!str || !*str)
		return (g_global.exit_status = 127, dis_fun(), NULL);
	if (stat(str, &data) == 0 && S_ISDIR(data.st_mode))
		return (ft_perror(str, ": is a directory"), NULL);
	if (str[0] == '/')
	{
		args = ft_split(str, ' ');
		path = ft_strdup(args[0]);
		free_fun(args);
	}
	else if (str[0] == '.' && str[1] == '/' && access(str, X_OK) == -1)
	{
		g_global.exit_status = 126;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (NULL);
	}
	else
		path = ft_strdup(str);
	return (path);
}

char	*valid_path(char **str, char *val)
{
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = -1;
	if (*val == '/' || *val == '.' || !val || !*val)
		return (check_cmd(val));
	if (ft_strchr(val, '/'))
		return (ft_strdup(val));
	if (!str || !val)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		tmp1 = ft_strjoin(str[i], "/");
		tmp2 = ft_strjoin(tmp1, val);
		free(tmp1);
		if (access(tmp2, X_OK) == 0)
			return (ft_strdup(tmp2));
	}
	return (display_error(val), NULL);
}
