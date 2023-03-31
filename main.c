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

// check_list_path(t_list *list, t_env *list_env)
// {
// 	while(list)
// 	{
// 		if(list->trag == TOKEN_WORD)
// 		{
			
// 		}
// 		list = list->next;
// 	}
// }


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
		//check_list_path(list, list_env);
		node = list;
		while(list)
		{
			printf("%s ==> %d ***> %d\n", list->data, list->trag, list->flag);
			list = list->next;
		}
		list = node;
			printf("TTTTTTTTTTTTTTTTTTTTTTT\n");
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
				printf("outfile==> %s\n", (c_list)->outfile->data);
				(c_list)->outfile = (c_list)->outfile->next;
			}
			printf("|/////////////////////////////////////////////////////////|\n");
				(c_list) = (c_list)->next;
		}
		fill_clean_list(list, &c_list, list_env);
	}
	// fill_env(env, &list_env);
	// //get_current_path(list_env, "abc$USER*xyz$USER");
	// get_current_path(list_env, "$");
	return(0);
}
