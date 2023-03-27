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

int main(int ac, char **av, char **env)
{
	t_list *list;
		list = NULL;
	t_myshell *c_list;
	t_env *list_env;
	list_env = NULL;
	t_list *node;
	(void)ac;
	(void)av;
	while (1)
	{
		list = NULL;
		fill_env(env, &list_env);
		char  *line = readline("myshell> ");
		add_history(line);
		fill_list(line, &list);
		node = list;
		// while(list)
		// {
		// 	printf("%s ==> %d\n", list->data, list->trag);
		// 	list = list->next;
		// }
		fill_clean_list(node, &c_list, list_env);
	}
	// fill_env(env, &list_env);
	// //get_current_path(list_env, "abc$USER*xyz$USER");
	// get_current_path(list_env, "$");
	return(0);
}
