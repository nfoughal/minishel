#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_lstadd_back_args(t_arg **lst, t_arg *new)
{
	t_arg	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_arg	*ft_lstnew_args(char *data)
{
	t_arg	*p;

	p = (t_arg *)malloc(sizeof(t_arg));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back_outfile(t_outfile **lst, t_outfile *new)
{
	t_outfile	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_outfile	*ft_lstnew_outfile(char *data)
{
	t_outfile	*p;

	p = (t_outfile *)malloc(sizeof(t_outfile));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back_infile(t_infile **lst, t_infile *new)
{
	t_infile	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_infile	*ft_lstnew_infile(char *data)
{
	t_infile	*p;

	p = (t_infile *)malloc(sizeof(t_infile));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back_herdoc(t_herdoc **lst, t_herdoc *new)
{
	t_herdoc	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_herdoc	*ft_lstnew_herdoc(char *data)
{
	t_herdoc	*p;

	p = (t_herdoc *)malloc(sizeof(t_herdoc));
	if (!p)
		return (NULL);
	p->data = data;
	p->next = NULL;
	return (p);
}

void	ft_lstadd_back_myshell(t_myshell **lst, t_myshell *new)
{
	t_myshell	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_myshell	*ft_lstnew_myshell(t_arg *args, t_infile *infile, t_outfile *outfile)
{
	t_myshell	*a;

	a = (t_myshell *)malloc(sizeof(t_myshell));
	if (!a)
		return (NULL);
	a->args = args;
	a->infile = infile;
	a->outfile = outfile;
	a->next = NULL;
	return (a);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*p;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		p = *lst;
		while (p->next != NULL)
			p = p->next;
		p->next = new;
	}
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*p;

	p = (t_env *)malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->key = key;
	p->value = value;
	p->next = NULL;
	return (p);
}