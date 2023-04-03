#include "minishell.h"

void free_list(t_list *list)
{
	t_list *node;
	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void free_arg_list(t_arg *list)
{
	t_arg *node;
	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void free_outfile_list(t_outfile *list)
{
	t_outfile *node;
	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void free_infile_list(t_infile *list)
{
	t_infile *node;
	while (list)
	{
		node = list->next;
		free(list->data);
		list->data = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void free_env_list(t_env *list)
{
	t_env *node;
	while (list)
	{
		node = list->next;
		free(list->key);
		free(list->value);
		list->key = NULL;
		list->value = NULL;
		free(list);
		list = NULL;
		list = node;
	}
}

void init_myshell(t_myshell *init)
{
	init->args = NULL;
	init->infile = NULL;
	init->outfile = NULL;
}

int check_error(t_list *tokens)
{
	int db_q = 0;
	int sb_q = 0;
	if (ft_lstsize(tokens) == 0)
		return(0);
	if (tokens->trag == TOKEN_PIPE)
		return (printf("Synatx Error\n"));
	while (tokens)
	{
		if (tokens->trag == TOKEN_GREATER_THAN || tokens->trag == TOKEN_LESS_THAN 
		|| tokens->trag == TOKEN_HERDOC || tokens->trag == TOKEN_REDIRECTION)
		{
			if (!tokens->next)
				return (printf("Synatx Error\n"));
			else if (tokens->next->trag != TOKEN_WORD 
			&& tokens->next->trag != TOKEN_DOUBLE_OUTE 
			&& tokens->next->trag != TOKEN_SINGLE_OUTE)
				return (printf("Synatx Error\n"));
		}
		if (tokens->trag == TOKEN_DOUBLE_OUTE)
			db_q++;
		if (tokens->trag == TOKEN_SINGLE_OUTE)
			sb_q++;
		tokens = tokens->next;
	}

	if (sb_q % 2 != 0 || db_q % 2 != 0)
		return (printf("Synatx Error\n"));
	return 0;
}
void free_shell(t_myshell *list)
{
	t_myshell *node;
	while (list)
	{
		node = list->next;
		free_arg_list(list->args);
		free_infile_list(list->infile);
		free_outfile_list(list->outfile);
		free(list);
		list = node;
	}
}


void free_fun(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	t_list *list;
		list = NULL;
	t_myshell *c_list;
	t_env *list_env;
	list_env = NULL;
	c_list = NULL;
	t_list *node;
	node = list;
	(void)ac;
	(void)av;
	while (1)
	{
		atexit(free_fun);
		list = NULL;
		list_env = NULL;
		c_list = NULL;
		fill_env(env, &list_env);
		char  *line = readline("myshell> ");
		add_history(line);
		fill_list(line, &list);
		// if (check_error(list) != 0)
		// 	continue;
		fill_clean_list(list, &c_list, list_env);
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
		// 		printf("outfile==> %s *** %d\n", (c_list)->outfile->data, (c_list)->outfile->flag);
		// 		(c_list)->outfile = (c_list)->outfile->next;
		// 	}
		// 	printf("|/////////////////////////////////////////////////////////|\n");
		// 		(c_list) = (c_list)->next;
		// }
		free(line);
		free_list(list);
		free_env_list(list_env);
		free_shell(c_list);
	}
	return(0);
}





// printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
// while(list)
// {
// 	printf("%s ==> %d ***> %d ++++++> %d \n", list->data, list->trag, list->flag, list->out_flag);
// 	list = list->next;
// }
