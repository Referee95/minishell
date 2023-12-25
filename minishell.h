/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:08:30 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/13 09:25:59 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SIMPLE_CMD 1
# define COMPOUND_CMD 2
# define TRUE 1
# define FALSE 0

# include <stdio.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

enum	e_type
{
	IN,
	OUT,
	APPEND,
};

typedef struct s_redir
{
	char			*f;
	enum e_type		type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_scmd
{
	t_list			*words;
	t_redir			*redirs;
	int				fd;
}					t_scmd;

typedef struct s_ccmd
{
	int				num_scmds;
	int				type;
	t_scmd			*simple_command;
	t_scmd			**compound_command;
}					t_ccmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

struct s_glo
{
	int				exit_st;
	struct s_env	*env;
}	t_glo;

struct s_glo	g_glo;

//Lexer && parsing
int					token_len(char *line);
t_list				*lexer(char *line);
int					check_last_node(t_list **tokens);
int					analyzer(t_list *tokens, char *token);
int					num_scmds(t_list *tokens);
t_ccmd				*parse_ccmd(t_list *tokens, t_env *envlist);
t_redir				*ft_redirnew(char *content, enum e_type type);
void				rediradd_back(t_redir **lst, t_redir *new);
void				setup_heredoc(char *delimiter, t_scmd *scmd,
						t_env *envlist);

// expansion
t_env				*ft_get_env(char **env);
char				*remove_quotes(char *s_tok);
char				*expand_heredoc(char *tok, t_env *envlist);
char				*expand_variable(char *exp_line, char *sub_line,
						t_env *envlist, int check);
char				*expand_var_(char *exp_line, char *tok, t_env *envlist,
						int *i);
char				*expand_var(char *exp_line, char *tok, t_env *envlist,
						int *i);
int					dolar_len_(char *str, int *i);
char				*join_character(char *str, char c);
char				*replace_quotes(char *exp_line, char *tok, int *i,
						char *quote);
t_list				*expanded_list(t_list *lst, t_env *envlist);
t_redir				*expanded_redir(t_redir *redir, t_env *envredir);

//signals
void				handle_ctrl_c(int sig_num);
void				ft_signals(void);

// executer
int					len_arr(char **arr);
int					arg_is_digit(char *str);
void				c_echo(char **str);
void				c_pwd(void);
void				c_cd(char **str);
int					c_env(char **str);
void				c_exit(char **str);
void				c_export(t_env *env, char **str);
void				c_unset(t_env *envlist, char **str);
void				ft_remove(char *str);
int					ft_handler_unset(char *str);
t_env				*ft_envnew(char *key, char *value);
char				**env_to_str(t_env *env);
char				*get_value(char *env);
char				*get_key(char *env);
void				ft_envadd_back(t_env **envlist, t_env *new);
int					ft_builtin(t_scmd *cmd, t_env *cur, char **str);
void				ft_free(char **arr);
void				command_export(t_env *envlist, char **str);
int					is_builtin(char **str);
int					execute_builtins(char **str, t_env *cur);
char				*get_path(char **str, t_env *env);
void				first_cmd(int *p1, int *p2);
void				in_two_pipe(int *p1, int *p2);
void				in_two_pipe2(int *p1, int *p2);
void				last_pipe(int *p1, int *p2);
void				last_pipe2(int *p1, int *p2);
void				create_pipe(int i, int *p1, int *p2);
void				ft_pipe(int i, int *p1, int *p2, int num);
void				c_pipe(int p1[2], int p2[2]);
void				close_p(int *p1, int *p2);
int					setup_redirections(t_redir *redir, t_env *env);
char				**setup_cmd_arguments(t_list *lst, t_env *cur);
void				executer(t_ccmd *cmd, t_env **envlist);
int					execute_cmd(t_scmd *cmd, t_env *cur);
int					execute_simple(t_scmd *cmd, t_env *cur);
int					execute_cmp(t_ccmd *cmd, t_env *env, int j, int i);
void				print_error(char *s1, char *s2, char *s3);

//free
void				free_tokens(t_list *tokens);
void				free_redir(t_redir *tokens);
void				free_all(t_list *tokens, t_ccmd *cmd, char *input);
void				free_env(void);
void				ft_free_env(t_env *cur);
#endif