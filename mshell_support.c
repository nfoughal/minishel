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

char *remove_cout(char *str)
{
	int i = 0;
	char *p;
	char *start;
	start = str;
	//int j = 0;
	while(*str)
	{
		while(*str == '\"' || *str == '\'')
			str++;
		i++;
		str++;
	}
	p = malloc(sizeof(char) * (i + 1));
	if(!p)
		return (0);
	i = 0;
	str = start;
	while(*str)
	{
		while(*str == '\"' || *str == '\'')
			str++;
		p[i] = *str;
		i++;
		if(*str == '\0')
			break;
		str++;
	}
	p[i] = '\0';
	return (p);
}

char *get_string(t_list **list, t_env *list_env)
{
	
	char *string;
	char *str;
	string = "";
	while((*list) && (*list)->trag != TOKEN_PIPE && (*list)->flag != TOKEN_ESPACE &&
	(*list)->trag != TOKEN_GREATER_THAN && (*list)->trag != TOKEN_LESS_THAN 
	&& (*list)->trag != TOKEN_PIPE && (*list)->trag != TOKEN_HERDOC && (*list)->trag != TOKEN_REDIRECTION
	)
	{
		if ((*list)->trag == TOKEN_WORD_SINGLE_COUT)
			string = ft_strjoin(string, (*list)->data);
		else if ((*list)->trag == TOKEN_WORD)
			string = ft_strjoin(string, get_current_path(list_env, (*list)->data));
		(*list) = (*list)->next;
	}
	if ((*list) && (*list)->flag == TOKEN_ESPACE && (*list)->trag == TOKEN_WORD)
	{
		string = ft_strjoin(string, get_current_path(list_env, (*list)->data));
		(*list) = (*list)->next;
	}
	if ((*list) && ((*list)->trag == TOKEN_SINGLE_OUTE || (*list)->trag == TOKEN_DOUBLE_OUTE))
		(*list) = (*list)->next;
	// str = remove_cout(string);
	return (string);
}