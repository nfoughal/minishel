#include "minishell.h"

void free_list()
{
		// node = list;
		// free(line);
		// while (list)
		// {
		// 	node = list->next;
		// 	free(list->data);
		// 	list->data = NULL;
		// 	free(list);
		// 	list = NULL;
		// 	list = node;
		// }

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
	if (tokens->trag == TOKEN_PIPE)
		return (printf("Synatx Error\n"));
	while (tokens)
	{
		if (tokens->trag == TOKEN_GREATER_THAN || tokens->trag == TOKEN_LESS_THAN || tokens->trag == TOKEN_PIPE || tokens->trag == TOKEN_HERDOC || tokens->trag == TOKEN_REDIRECTION)
		{
			if (!tokens->next)
				return (printf("Synatx Error\n"));
			else if (tokens->next->trag != TOKEN_WORD && tokens->next->trag != TOKEN_DOUBLE_OUTE && tokens->next->trag != TOKEN_SINGLE_OUTE)
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

int main(int ac, char **av, char **env)
{
	t_list *list;
		list = NULL;
	t_myshell *c_list;
	t_env *list_env;
	list_env = NULL;
	t_list *node;
		//node = list;
	(void)ac;
	(void)av;
	while (1)
	{
		list = NULL;
		fill_env(env, &list_env);
		char  *line = readline("myshell> ");
		add_history(line);
		fill_list(line, &list);
		if (check_error(list) != 0)
			continue;
		node = list;
		fill_clean_list(list, &c_list, list_env);
		while((c_list))
		{
			while((c_list)->args)
			{
				printf("args==> %s\n", (c_list)->args->data);
				(c_list)->args = (c_list)->args->next;
			}
			while((c_list)->infile)
			{
				printf("infile==> %s\n", (c_list)->infile->data);
				(c_list)->infile = (c_list)->infile->next;
			}
			while((c_list)->outfile)
			{
				printf("outfile==> %s *** %d\n", (c_list)->outfile->data, (c_list)->outfile->flag);
				(c_list)->outfile = (c_list)->outfile->next;
			}
			while((c_list)->herdoc)
			{
				printf("herdoc==> %s\n", (c_list)->herdoc->data);
				(c_list)->herdoc = (c_list)->herdoc->next;
			}
			printf("|/////////////////////////////////////////////////////////|\n");
				(c_list) = (c_list)->next;
		}
		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
		// while(list)
		// {
		// 	printf("%s ==> %d ***> %d ++++++> %d \n", list->data, list->trag, list->flag, list->out_flag);
		// 	list = list->next;
		// }
	}
	return(0);
}
