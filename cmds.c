/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:31:35 by moouaamm          #+#    #+#             */
/*   Updated: 2023/04/16 04:55:40 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	k;

	k = 0;
	if (*str == '-')
	{
		str++;
		while (*str && *str == 'n')
			str++;
		if (!*str && *(--str) == 'n')
			return (1);
	}
	return (0);
}

char	*ft_getval_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (str_dup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	dash_n(t_arg **argm, int *no_line)
{
	while ((*argm) && check_n((*argm)->data) == 1)
	{
		*no_line = 1;
		(*argm) = (*argm)->next;
	}
}

int	echocmd(t_arg *argm, t_env *env)
{
	int	i;
	int	no_line;

	(void)env;
	no_line = 0;
	if (argm != NULL)
		dash_n(&argm, &no_line);
	else
		return (printf("\n"), 1);
	i = 1;
	while (argm)
	{
		if (i > 1)
			printf(" ");
		printf("%s", argm->data);
		argm = argm->next;
		i++;
	}
	if (!no_line)
		printf("\n");
	g_global.exit_status = 0;
	return (1);
}

int	pwdcmd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		g_global.exit_status = 0;
		return (ft_putendl_fd(cwd, 1), 1);
	}
	else
	{
		g_global.exit_status = 1;
		return (perror("getcwd() error"), -1);
	}
}
// while((c_list))
// {
// 	while((c_list)->args)
// 	{
// 		printf("args==> %s\n", (c_list)->args->data);
// 		(c_list)->args = (c_list)->args->next;
// 	}
// 	while((c_list)->infile)
// 	{
// 		printf("infile==> %s\n", (c_list)->infile->data);
// 		(c_list)->infile = (c_list)->infile->next;
// 	}
// 	while((c_list)->outfile)
// 	{
// 		printf("outfile==> %s\n", (c_list)->outfile->data);
// 		(c_list)->outfile = (c_list)->outfile->next;
// 	}
// 	// while((c_list)->herdoc)
// 	// {
// 	// 	printf("herdoc==> %s\n", (c_list)->herdoc->data);
// 	// 	(c_list)->herdoc = (c_list)->herdoc->next;
// 	// }
// 	printf("|/////////////////////////////////////////////////////////|\n");
// 		(c_list) = (c_list)->next;
// }
// printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
// while(list)
// {
// 	printf("%s ==> %d ***> %d ++++++> %d \n",
// list->data, list->trag, list->flag, list->out_flag);
// 	list = list->next;
// }