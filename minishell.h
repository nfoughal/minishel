/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:23:41 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/03 17:41:27 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<unistd.h>
# include<fcntl.h>
# include<stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h" 

# define TOKEN_PIPE 1
# define TOKEN_SINGLE_OUTE 2
# define TOKEN_DOUBLE_OUTE 3
# define TOKEN_WORD 4
# define TOKEN_LESS_THAN 5
# define TOKEN_GREATER_THAN 6
# define TOKEN_HERDOC 7
# define TOKEN_REDIRECTION 8
# define TOKEN_WORD_SINGLE_COUT 9
# define TOKEN_ESPACE 10
# define TOKEN_DOUBLE_RED 11

typedef struct s_infile
{
	char			*data;
	struct s_infile	*next;
}t_infile;

typedef struct s_outfile
{
	int					flag;
	char				*data;
	struct s_outfile	*next;
}t_outfile;

typedef struct s_arg
{
	char			*data;
	struct s_arg	*next;
}t_arg;

typedef struct s_myshell
{
	t_arg				*args;
	t_infile			*infile;
	t_outfile			*outfile;
	struct s_myshell	*next;
}t_myshell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_all_list
{
	t_arg		*list_arg;
	t_infile	*list_infile;
	t_outfile	*list_outfile;
}t_all_list;

void		fill_list(char *line, t_list **list);
int			ft_strcmp(const char *s1, const char *s2);
void		init_myshell(t_myshell *init);
void		fill_clean_list(t_list *list, t_myshell **c_list, t_env *list_env);
void		ft_lstadd_back_args(t_arg **lst, t_arg *new);
void		ft_lstadd_back_outfile(t_outfile **lst, t_outfile *new);
void		ft_lstadd_back_infile(t_infile **lst, t_infile *new);
void		ft_lstadd_back_myshell(t_myshell **lst, t_myshell *new);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*ft_lstnew_env(char *key, char *value);
t_arg		*ft_lstnew_args(char *data);
t_outfile	*ft_lstnew_outfile(char *data);
t_infile	*ft_lstnew_infile(char *data);
t_myshell	*ft_lstnew_myshell(t_arg *args, t_infile *infile,
				t_outfile *outfile);
void		fill_env(char **env, t_env **list_env);
char		*get_current_path(t_env *list_env, char *str, int i);
char		*get_value_from_env(t_env *list_env, char *key);
char		*get_string(t_list **list, t_env *list_env, int herdoc_flag);
int			herdoc_check(char *line, t_list **list);
int			ft_line(char *line);
int			between_q_count(char **line);
void		fill_cout(char **line, t_list **list, int j);
void		check_quotes(char **line, t_list **list);
void		list_dup(char *line, t_list **list, int *ifdup, t_list **new1);
void		if_herdoc_valid(char **line, t_list **list, int *flag);
void		fill_tokens(t_list **list, char **line);
void		skeep_spaces(char **line, t_list **new1, int *ifdup);
char		*str_dup(char *line);
void		fill_outfile_list(t_outfile **list_outfile,
				t_list **list, t_env *list_env);
void		fill_file(int file, char *dill);
void		fill_herdoc_file(t_list **list, t_infile **list_infile,
				t_env *list_env, int i);
void		fill_myshell(t_list **list, t_all_list *pp, t_myshell **c_list);
void		free_list(t_list *list);
void		free_arg_list(t_arg *list);
void		free_outfile_list(t_outfile *list);
void		free_infile_list(t_infile *list);
void		free_env_list(t_env *list);
void		free_shell(t_myshell *list);
void		free_all(char *e, char *f, char *value, char *result);
int			check_next(t_list *tokens);
int			token_loop(t_list *tokens, char *line, int *db_q, int *sb_q);
int			check_error(t_list *tokens, char *line);
#endif