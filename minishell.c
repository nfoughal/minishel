#include "minishell.h"

void fill_clean_list(t_list *list, t_myshell **c_list, t_env *list_env)
{
	t_arg *list_arg;
	t_herdoc *list_herdoc;
	t_infile *list_infile;
	t_outfile *list_outfile;
	list_arg = NULL;
	list_herdoc = NULL;
	list_infile = NULL;
	list_outfile = NULL;
	t_list *node = list;
	int herdoc_flag = 0;
	while(list)
	{
		if(list->next  && (list->trag == TOKEN_GREATER_THAN || list->trag == TOKEN_REDIRECTION))
		{
			list = list->next;
			ft_lstadd_back_outfile(&list_outfile, ft_lstnew_outfile(get_string(&list, list_env, &herdoc_flag)));

		}
		else if(list->next  && (list->trag == TOKEN_LESS_THAN))
		{
			list = list->next;
			ft_lstadd_back_infile(&list_infile, ft_lstnew_infile(get_string(&list, list_env, &herdoc_flag)));
		}
		else if(list->next && (list->trag == TOKEN_HERDOC))
		{
			herdoc_flag = 1;
			list = list->next;
			ft_lstadd_back_herdoc(&list_herdoc, ft_lstnew_herdoc(get_string(&list, list_env, &herdoc_flag)));
			herdoc_flag = 0;
		}
		else
			ft_lstadd_back_args(&list_arg, ft_lstnew_args(get_string(&list, list_env, &herdoc_flag)));
		if (list == NULL || list->trag == TOKEN_PIPE)
		{
			ft_lstadd_back_myshell(c_list, ft_lstnew_myshell(list_arg, list_infile, list_outfile, list_herdoc));
			list_arg = NULL;
			list_infile = NULL;
			list_herdoc = NULL;
			list_outfile = NULL;
			if (list)
				list = list->next;
		}
	}
}

//ls< her "-la heh" | cat | cat > out | << "GER   DOC" | ls >> out | echo '$PATH' | echo "$TMPDIR" | echo "abc$USER*xyz$USER"