#include "minishell.h"

int herdoc_check(char *line, t_list **list)
{
	char *p;
	t_list *new;

	if ((ft_strncmp(line, ">>", 2) == 0) || (ft_strncmp(line, "<<", 2) == 0))
	{
		p = malloc(sizeof(char) * 3);
		p[0] = *line;
		p[1] = *line;
		p[2] = '\0';
		new = ft_lstnew(p);
		ft_lstadd_back(list, new);
		if(*line == '<')
		{
			new->trag = TOKEN_HERDOC;
			return (2);
		}
		if(*line == '>')
		{
			new->trag = TOKEN_REDIRECTION;
			return (1);
		}
	}
	return (0);
}

int ft_line(char *line)
{
	int i;
	i = 0; // line[i] != ' ' &&
	while(line[i] != ' ' && line[i] != '>' && line[i] != '<' && line[i] 
			!= '\"' && line[i] != '\'' && line[i] != '|' && line[i])
			i++;
	return (i);
}

char *str_dup(char *line)
{
	int i = 0;
	int len = ft_line(line);
	if(len == 0)
		return(NULL);
	char *p = malloc(sizeof(char) * len);
	while(i < len)
	{
		p[i] = *line;
		i++;
		line++;
	}
	p[i] = '\0';
	return (p);
}
int between_q_count(char **line)
{
	int count = 0;
	int i = 0;
	while((*line)[i] && ((*line)[i] != '\"' || (*line)[i] != '\''))
	{
		i++;
		count++;
	}
	return (count);
}
void check_quotes(char **line, t_list **list, int *trag)
{
	int count = 0;
	t_list *new;
	int i = 0;
	char *s;
	char *p;
	//printf("%d\n\n\n", *trag);
	{
		p = malloc(sizeof(char) * 2);
		p[0] = **line;
		p[1] = '\0';
		new = ft_lstnew(p);
		ft_lstadd_back(list, new);
		if(**line == '\"')
			new->trag = TOKEN_DOUBLE_OUTE;
		else
			new->trag = TOKEN_SINGLE_OUTE;
		(*line)++;
	}
	count = between_q_count(line);
	s = malloc(sizeof(char) * count);
	while((**line) && (**line != '\"' && **line != '\''))
	{
		s[i] = **line;
		(*line)++;
		i++;
	}
	s[i] = '\0';
	new = ft_lstnew(s);
	ft_lstadd_back(list, new);
	if(*trag != 1 && **line == '\"')
	new->trag = TOKEN_WORD;
	if(*trag != 1 && **line == '\'')
	new->trag = TOKEN_WORD_SINGLE_COUT;
	*trag = 0;
	if(**line == '\"' || **line == '\'' )
	{
		p = malloc(sizeof(char) * 2);
		p[0] = **line;
		p[1] = '\0';
		new = ft_lstnew(p);
		ft_lstadd_back(list, new);
		if(**line == '\"')
			new->trag = TOKEN_DOUBLE_OUTE;
		else
			new->trag = TOKEN_SINGLE_OUTE;
		(*line)++;
	}
}

void fill_list(char *line, t_list **list)
{
	char *p;
	int flag;
	int trag = 0;
	char *dup;
	t_list *new;
	int cheker;
	while(*line == ' ')
		line++;
	while(*line)
	{
		flag = 0;
		dup = str_dup(line);
		if(dup != NULL)
		{
			new = ft_lstnew(dup);
			ft_lstadd_back(list, new);
			if(trag != 1)
				new->trag = TOKEN_WORD;
			trag = 0;
		}
		while(*line != ' ' && *line != '>' && *line != '<' && *line   // ls< her "-la heh" | cat | cat > out | << "GER   DOC" | ls >> out | echo '$PATH' | echo "$TMPDIR"
				!= '\"' && *line != '\'' && *line != '|' && *line)
			line++;
		if(*line == '\"' || *line == '\'')
			check_quotes(&line, list, &trag);
		
		if(*line == '>' || *line == '<')
		{
			if ((cheker = herdoc_check(line, list)) != 0)
			{
				line += 2;
				flag = 1;
				trag = 1;
			}
		}
		if((*line == '>' || *line == '<' || *line == '|') && (flag == 0))
		{
			p = malloc(sizeof(char) * 2);
			p[0] = *line;
			p[1] = '\0';
			new = ft_lstnew(p);
			ft_lstadd_back(list, new);
			if(*line == '|')
				new->trag = TOKEN_PIPE;
			else if(*line == '>')
			{
				new->trag = TOKEN_GREATER_THAN;
				trag = 1;
			}
			else if(*line == '<')
			{
				new->trag = TOKEN_LESS_THAN;
				trag = 1;
			}
			line++;
		}
		while(*line == ' ')
			line++;
	}
}
