#include "minishell.h"

void fill_env(char **env, t_env **list_env)
{
	int i = 0;
	int j = 0;
	int k;
	while(env[i])
	{
		j = 0;
		while(env[i][j] != '=')
			j++;
		k = j + 1;
		ft_lstadd_back_env(list_env, ft_lstnew_env(ft_substr(env[i], 0, j), ft_strdup(env[i] + k)));
		i++;
	}
	// while(list_env)
	// {
	// 	printf("key is ==> %s and value ==> %s\n", list_env->key, list_env->value);
	// 	list_env = list_env->next;
	// }
}