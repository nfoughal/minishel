#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h" 

#define TOKEN_PIPE 1
#define TOKEN_SINGLE_OUTE 2
#define TOKEN_DOUBLE_OUTE 3
#define TOKEN_WORD 4
#define TOKEN_LESS_THAN 5
#define TOKEN_GREATER_THAN 6
#define TOKEN_HERDOC 7
#define TOKEN_REDIRECTION 8
#define TOKEN_WORD_SINGLE_COUT 9
#define TOKEN_ESPACE 10
#define TOKEN_DOUBLE_RED 11

typedef struct s_herdoc
{
	char *data;
	struct s_herdoc *next;
}t_herdoc;

typedef struct s_infile
{
	char *data;
	struct s_infile *next;
}t_infile;

typedef struct s_outfile
{
	int flag;
	char *data;
	struct s_outfile *next;
}t_outfile;

typedef struct s_arg
{
	char *data;
	struct s_arg *next;
}t_arg;

typedef struct s_myshell
{
	t_arg *args;    //ls -la heh
	t_infile 	*infile;
	t_outfile 	*outfile;
	t_herdoc    *herdoc;
	struct s_myshell *next;
}t_myshell;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next; 
}t_env;

void fill_list(char *line, t_list **list);
int	ft_strcmp(const char *s1, const char *s2);
void init_myshell(t_myshell *init);
void fill_clean_list(t_list *list, t_myshell **c_list, t_env *list_env);
void	ft_lstadd_back_args(t_arg **lst, t_arg *new);
void	ft_lstadd_back_outfile(t_outfile **lst, t_outfile *new);
void	ft_lstadd_back_infile(t_infile **lst, t_infile *new);
void	ft_lstadd_back_herdoc(t_herdoc **lst, t_herdoc *new);
void	ft_lstadd_back_myshell(t_myshell **lst, t_myshell *new);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *key, char *value);
t_arg	*ft_lstnew_args(char *data);
t_outfile	*ft_lstnew_outfile(char *data);
t_infile	*ft_lstnew_infile(char *data);
t_herdoc	*ft_lstnew_herdoc(char *data);
t_myshell	*ft_lstnew_myshell(t_arg *args, t_infile *infile, t_outfile *outfile, t_herdoc *herdoc);
void fill_env(char **env, t_env **list_env);
char *get_current_path(t_env *list_env, char *str);
char *get_value_from_env(t_env * list_env, char *key);
char *get_string(t_list **list, t_env *list_env, int *herdoc_flag);

