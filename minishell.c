#include "minishell.h"

void fill_clean_list(t_list *list, t_myshell **c_list, t_env *list_env)
{
	t_arg *list_arg;
	t_herdoc *list_herdoc;
	t_infile *list_infile;
	t_outfile *list_outfile;
	t_outfile *new;
	list_arg = NULL;
	list_herdoc = NULL;
	list_infile = NULL;
	list_outfile = NULL;
	t_list *node = list;
	int herdoc_flag = 0;
	int flag = 0;
	while(list)
	{
		if(list->next  && (list->trag == TOKEN_GREATER_THAN || list->trag == TOKEN_REDIRECTION))
		{
			if(list->trag == TOKEN_REDIRECTION)
			{
				list = list->next;
				new = ft_lstnew_outfile(get_string(&list, list_env, &herdoc_flag));
				ft_lstadd_back_outfile(&list_outfile, new);
				new->flag = TOKEN_DOUBLE_RED;
			}
			else
			{
				list = list->next;
				ft_lstadd_back_outfile(&list_outfile, ft_lstnew_outfile(get_string(&list, list_env, &herdoc_flag)));
			}

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
			char *line;
			char *dill = get_string(&list, list_env, &herdoc_flag);
			int i = 100;
			int	file;
			while (access(ft_strjoin("/tmp/herdoc", ft_itoa(i)), F_OK) == 0)
				i++;
			file = open(ft_strjoin("/tmp/herdoc", ft_itoa(i)), O_CREAT | O_WRONLY, 0777);
			
			while ((line = readline("> ")))
			{
				if(ft_strcmp(dill, line) == 0)
					break;
				write(file, line, ft_strlen(line));
				write(file, "\n", 1);
			}
			
			ft_lstadd_back_infile(&list_infile, ft_lstnew_infile(ft_strjoin("/tmp/herdoc", ft_itoa(i))));
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