/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moouaamm <moouaamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:23:41 by nfoughal          #+#    #+#             */
/*   Updated: 2023/04/16 22:20:58 by moouaamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<signal.h>
# include<unistd.h>
# include<fcntl.h>
# include<stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <limits.h>

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
# define TOKEN_WORD_DOUBLE_COUT 12
# define EXECUTION 100
# define HERE_DOC 200
# define READING 300

typedef struct s_infile
{
	int				number;
	char			*data;
	struct s_infile	*next;
}t_infile;

typedef struct s_outfile
{
	int					number;
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
	int					fd_errorfile;
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
	t_list		*new_list;
	t_list		*old_next;
	t_list		*new;
	int			save;
	char		*f;
	char		*e;
	char		*result;
	char		*value;
	int			b;
	int			len;
	char		*s;
	int			i;
	char		*string;
	char		*ret;
	char		*re;
	char		*strstr_re;
	char		*p;
	char		*oldstr;
	int			oldstr_len;
	int			sub_len;
	int			repp_len;
	int			flag;
	int			j;
	t_infile	*new1;
	t_list		*list;
	t_myshell	*c_list;
	t_env		*list_env;
	char		*line;
	int			out;
	int			in;
}t_all_list;

typedef struct s_vb
{
	int		i;
	t_list	*freeable;
	int		read_stat;
	int		fd;
	int		n_iterations;
	int		exit_status;
	int		cerr;
	int		true_herdoc;
	int		fd_infile;
	int		fd_outfile;
	int		in_first;
	int		in_cltc;
	int		envflag;
	t_env	*env;
	int		dill_flag;
}t_g_vb;

t_g_vb	g_global;

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
char		*get_current_path(t_env *list_env, char *str, int i, int trag);
char		*get_value_from_env(t_env *list_env, char *key);
char		*get_string(t_list **list, t_env *list_env, int herdoc_flag);
int			herdoc_check(char *line, t_list **list);
int			ft_line(char *line);
int			between_q_count(char **line, int flag);
void		fill_cout(char **line, t_list **list, int j);
void		check_quotes(char **line, t_list **list);
void		list_dup(char *line, t_list **list, int *ifdup, t_list **new1);
void		if_herdoc_valid(char **line, t_list **list, int *flag);
void		fill_tokens(t_list **list, char **line);
void		skeep_spaces(char **line, t_list **new1, int *ifdup);
char		*str_dup(char *line);
void		fill_outfile_list(t_outfile **list_outfile,
				t_list **list, t_env *list_env);
void		fill_file(int file, char *dill, t_env *env);
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
void		free_list_joiner(void);
void		fill_new_list(t_all_list *pp, char **splited, t_list **list);
void		list_joine(t_list **list, t_env *list_env);
void		fill_p(t_all_list *pp, char *str_repp);
char		*string_replace(char *string, char *sub, char *str_repp);
int			if_valid_char(char c);
char		*get_string_len(char *str);
char		*data_replace(char *result, char *str, t_env *env);
void		free_main(char *line, t_list *list, t_myshell *c_list);
void		fill_s(char **line, t_all_list *pp);

//build in functions

int			sig_handling(void);
int			cdcmd(t_myshell *shell, t_env *envi);
int			pwdcmd(void);
int			echocmd(t_arg *argm, t_env *env);
int			envcmd(t_env *my_variables);
int			unsetcmd(t_env **env, t_arg *var);
int			exitcmd(t_arg *stat);
int			exportcmd(t_env **env, t_arg *args);
int			is_built_incmd(t_myshell *c_list, t_env **list_env);
int			is_execuve_cmd(t_myshell *c_list, t_env **list_env,
				int in, int out);
void		ft_close(int fd);
int			child_process(t_myshell *c_list, t_env *list_env);
char		**env_to_str(t_env *list);
char		*valid_path(char **str, char *val);
char		*check_cmd(char *str);
void		free_fun(char **str);
char		*true_path(t_env *env);
char		**get_options(t_arg *options);
int			alt_export(t_env **env, t_arg *args);
int			key_notexist(t_env *env, char *key);
char		*get_newvalue(char *key);
int			is_verified(char *str);
int			change_env(t_env **env, char *attr, char *old_key);
int			only_export(t_env **env);
int			handle_output(t_outfile *out, int dupout, int dupin);
int			handle_input(t_infile *in, int dupin, int dupout);
void		add_env_var(char *new_key, char *new_value, t_env **env, int flag);
void		ft_get_newkey(char **key, char *str, int i, int flag);
void		_null_value(char *attr, t_env **env);
void		there_is_equal(t_arg **args, int flag, int i, t_env **env);
int			in_out_handling(t_infile *infile, t_outfile *outfile,
				int in, int out);
int			get_exit_status(int psid);
int			main_help(t_myshell *c_list, t_env **list_env, int out, int in);
int			one_cmd(t_myshell *c_list, t_env **list_env, int out, int in);
int			more_cmds(t_myshell *c_list, t_env *list_env);
int			check_is_buildin(t_arg *args);
void		add_status(t_env **list);
void		ft_close(int fd);
int			loop_inf(t_all_list *all);
int			display_error(char *str);
void		ft_perror(char *str, char *error);
int			ft_isumber(char *str);
char		*ft_strjoin2(char const *s1, char const *s2);
int			unset_more(t_env **env, t_arg *var);
int			is_flagged(t_list **list);
int			exportcmd2(t_env **env, t_arg *args);
int			verified_unset(char *str);
void		ft_close2(int fd1, int fd2, int fd3);
void		dis_fun(void);

#endif