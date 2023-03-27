#include "minishell.h"

char *get_value_from_env(t_env * list_env, char *key)
{
	while(list_env)
	{
		
		if(ft_strcmp(list_env->key, key) == 0)
			return list_env->value;
		list_env = list_env->next;
	}
	return "";
}


char *get_current_path(t_env *list_env, char *str)
{
	int i = 0;
	int save;
	char *f;
	char *e;
	char *result;
	
	while(ft_strchr(str, '$'))
	{
		while(str[i] != '$')
		i++;
		f = ft_substr(str, 0, i);
		i++;
		save = i;
		while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		e = ft_substr(str + i, 0, ft_strlen(str) - i);
		result = ft_strjoin(f, get_value_from_env(list_env, ft_substr(str, save, i - save)));
		str = ft_strjoin(result, e);
	}
	return str;
}


