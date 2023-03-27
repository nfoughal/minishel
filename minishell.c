#include "minishell.h"

void fill_clean_list(t_list *list, t_myshell **c_list, t_env *list_env)
{

	t_arg *list_arg;
	t_herdoc *list_herdoc;
	t_infile *list_infile;
	t_outfile *list_outfile;
	t_arg *list_arg1;
	t_herdoc *list_herdoc1;
	t_infile *list_infile1;
	t_outfile *list_outfile1;
	list_arg = NULL;
	list_herdoc = NULL;
	list_infile = NULL;
	list_outfile = NULL;
	t_list *node = list;
	while(list)
	{
		if(list->trag == TOKEN_GREATER_THAN || list->trag == TOKEN_REDIRECTION)
		{
			if ((ft_strcmp(list->next->data, "\"") == 0) || (ft_strcmp(list->next->data, "\'") == 0))
				ft_lstadd_back_outfile(&list_outfile, ft_lstnew_outfile(list->next->next->data));
			else
				ft_lstadd_back_outfile(&list_outfile, ft_lstnew_outfile(list->next->data));
		}
		else if (list->trag == TOKEN_LESS_THAN)
		{
			if ((ft_strcmp(list->next->data, "\"") == 0) || (ft_strcmp(list->next->data, "\'") == 0))
				ft_lstadd_back_infile(&list_infile, ft_lstnew_infile(list->next->next->data));
			else
				ft_lstadd_back_infile(&list_infile, ft_lstnew_infile(list->next->data));
		}
		else if (list->trag == TOKEN_HERDOC)
		{
			if((ft_strcmp(list->next->data, "\"") == 0) || (ft_strcmp(list->next->data, "\'") == 0))
				ft_lstadd_back_herdoc(&list_herdoc, ft_lstnew_herdoc(list->next->next->data));
			else
				ft_lstadd_back_herdoc(&list_herdoc, ft_lstnew_herdoc(list->next->data));
		}
		else if(list->trag == TOKEN_WORD_SINGLE_COUT)
				ft_lstadd_back_args(&list_arg, ft_lstnew_args(list->data));
		else if(list->trag == TOKEN_WORD)
			ft_lstadd_back_args(&list_arg, ft_lstnew_args(get_current_path(list_env, list->data)));
		list = list->next;
	}
	list = node;
	list_arg1 = NULL;
	list_infile1 = NULL;
	list_herdoc1 = NULL;
	list_outfile1 = NULL;
	while(list)
	{
		if(list->trag == TOKEN_GREATER_THAN || list->trag == TOKEN_REDIRECTION)
		{
			if ((ft_strcmp(list->next->data, "\"") == 0) || (ft_strcmp(list->next->data, "\'") == 0))
				ft_lstadd_back_outfile(&list_outfile1, ft_lstnew_outfile(list->next->next->data));
			else
				ft_lstadd_back_outfile(&list_outfile1, ft_lstnew_outfile(list->next->data));
		}
		else if (list->trag == TOKEN_LESS_THAN)
		{
			if ((ft_strcmp(list->next->data, "\"") == 0) || (ft_strcmp(list->next->data, "\'") == 0))
				ft_lstadd_back_infile(&list_infile1, ft_lstnew_infile(list->next->next->data));
			else
				ft_lstadd_back_infile(&list_infile1, ft_lstnew_infile(list->next->data));
		}
		else if (list->trag == TOKEN_HERDOC)
		{
			if((ft_strcmp(list->next->data, "\"") == 0) || (ft_strcmp(list->next->data, "\'") == 0))
				ft_lstadd_back_herdoc(&list_herdoc1, ft_lstnew_herdoc(list->next->next->data));
			else
				ft_lstadd_back_herdoc(&list_herdoc1, ft_lstnew_herdoc(list->next->data));
		}
		else if(list->trag == TOKEN_WORD_SINGLE_COUT)
				ft_lstadd_back_args(&list_arg1, ft_lstnew_args(list->data));
		else if(list->trag == TOKEN_WORD)
			ft_lstadd_back_args(&list_arg1, ft_lstnew_args(get_current_path(list_env, list->data)));
		if (list->trag == TOKEN_PIPE || list->next == NULL)
		{
			ft_lstadd_back_myshell(c_list, ft_lstnew_myshell(list_arg1, list_infile1, list_outfile1, list_herdoc1));
			list_arg1 = NULL;
			list_infile1 = NULL;
			list_herdoc1 = NULL;
			list_outfile1 = NULL;
		}
		list = list->next;
	}
	printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	while(list_arg)
	{
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAARGG=>%s\n", list_arg->data);
		list_arg = list_arg->next;
	}
	while(list_infile)
	{
		printf("IIIIIIIIIIIIIIIIIIIIIIIIIIIFILE=>%s\n", list_infile->data);
		list_infile = list_infile->next;
	}
	while(list_outfile)
	{
		printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOUTFILE=%s\n", list_outfile->data);
		list_outfile = list_outfile->next;
	}
	while(list_herdoc)
	{
		printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHIRDOC=>%s\n", list_herdoc->data);
		list_herdoc = list_herdoc->next;
	}
		printf("################################################\n");
		while((*c_list))
		{
			while((*c_list)->args)
			{
				printf("args==> %s\n", (*c_list)->args->data);
				(*c_list)->args = (*c_list)->args->next;
			}
			while((*c_list)->infile)
			{
				printf("infile==> %s\n", (*c_list)->infile->data);
				(*c_list)->infile = (*c_list)->infile->next;
			}
			while((*c_list)->outfile)
			{
				printf("outfile==> %s\n", (*c_list)->outfile->data);
				(*c_list)->outfile = (*c_list)->outfile->next;
			}
			while((*c_list)->herdoc)
			{
				printf("herdoc==> %s\n", (*c_list)->herdoc->data);
				(*c_list)->herdoc = (*c_list)->herdoc->next;
			}
			printf("|/////////////////////////////////////////////////////////|\n");
				(*c_list) = (*c_list)->next;
		}
}


//ls< her "-la heh" | cat | cat > out | << "GER   DOC" | ls >> out | echo '$PATH' | echo "$TMPDIR" | echo "abc$USER*xyz$USER"