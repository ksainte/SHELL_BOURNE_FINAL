/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:02:06 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/09 10:48:18 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

// # include <linux/limits.h>
# include <sys/wait.h>

# define EXIT_NUMERIC_ERROR 255

extern void					rl_replace_line(const char *text, int clear_undo);

// signal_handler/SignalHandler.c
// void	signal_handler(int signum);
void						init_signal_handler(void);
void						initiliaze_signal(void);

// EnvironmentVariablemManager.c

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*prev;
	struct s_env			*next;
}							t_env;

typedef struct s_node
{
	int						type;
	char					*value;
	struct s_node			*next;
	struct s_node			*prev;
}							t_node;

typedef struct s_args
{
	char					*arg_value;
	struct s_args			*next;
}							t_args;

typedef struct s_redirect_in
{
	char					*name;
	int						type;
	int						fd;
	struct s_redirect_in	*next;
}							t_redirect_in;

typedef struct s_redirect_out
{
	char					*name;
	int						type;
	int						fd;
	struct s_redirect_out	*next;
}							t_redirect_out;

typedef struct s_cmd
{
	int						has_cmd;
	char					*name;
	struct s_args			*args;
	struct s_cmd			*next;
	struct s_redirect_in	*list_in;
	struct s_redirect_out	*list_out;
}							t_cmd;

typedef struct s_exec
{
	char					**tab;
	int						i;
	int						cmd_size;
	int						is_heredoc;
	int						in_pipe[2];
	int						out_pipe[2];
	char					*executable;
	int						has_access;
	int						is_in_child;

}							t_exec;

typedef struct s_fill
{
	int						return_value;
	int						i;
	int						len;
}							t_fill;

int							main_exit(void);
void						ft_init_fill(t_fill *fill);
void						init_signal_handler(void);
void						initiliaze_signal(void);
void						signal_to_default_behaviour(void);

int							initiliaze_envp(char **envp);
void						free_env_lst(t_env *env_lst);
char						*ft_strtok(char *str, char *delim);
char						*ft_strtok_reverse(char *str, char *delim);
int							add_env_lst(t_env **env_lst, char *key,
								char *value);
void						print_env_lst(int fd, int mode);
char						*search_value_env_lst(char *key);
int							edit_env_lst(t_env **env_lst, char *key,
								char *value);
int							delete_env_lst(t_env **env_lst, char *key);
void						expander(t_node **node_list);
char						**env_lst_to_tab(t_env *env_lst);
void						duplicate_env_lst(t_env **src, t_env **dest);
void						sort_env_lst(t_env **env_lst);
bool						is_escaped(const char *str, int pos);
int							ft_isalnum(int c);
char						*handle_double_dollar(char *result);
char						*handle_exit_status(char *result);
char						*handle_variable(char *result, const char *value,
								int *i);

// utils
void						ft_error(void);
void						ft_print_commands(t_node *node_list, t_cmd *cmd);
void						ft_print_table(char **tab);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char const *s, int fd);

// Exec in Childs
void						ft_execute_in_childs(t_cmd *cmd, t_exec *exec);
void						ft_exchange_pipes(t_exec *exec);
void						ft_close_pipes(t_exec *exec);
void						ft_current_cmd_table(t_cmd *cmd, t_exec *exec);
void						ft_launch_execution(t_cmd *cmd, t_exec *exec);

// Exec builtins in parent
void						ft_cd_in_parent(t_cmd *cmd, char **tab,
								int in_child);
void						ft_unset_in_parent(t_cmd *cmd, char **tab,
								int child);
void						ft_env_in_parent(t_cmd *cmd, char **tab,
								int in_child);
void						ft_echo_in_parent(t_cmd *cmd, char **tab,
								int in_child);
void						ft_export_in_parent(t_cmd *cmd, char **tab,
								int in_child);

// Printing utils

void						ft_print_table(char **tab);
void						print_node_list(t_node *node_list);
void						ft_print_table(char **tab);
void						ft_print_commands(t_node *node_list, t_cmd *cmd);

// Heredoc.c

int							handle_heredoc(t_redirect_in *cmd_in, int in_child);
void						ft_newline_to_null(char *str);
void						ft_null_to_newline(char *str);
int							ft_cmp_gnl_word(char *gnl, char *word);
int							ft_heredoc(t_redirect_in *cmd_in);
void						ft_putstr_fd(char const *s, int fd);
void						ft_putchar_fd(char c, int fd);

// execve
int							ft_is_builtin(char *str);
void						ft_execve(t_cmd *cmd);
char						*ft_get_cmd(char *str);
void						ft_newline_to_null(char *str);
void						ft_null_to_newline(char *str);
int							ft_cmp_gnl_word(char *gnl, char *word);
int							ft_heredoc(t_redirect_in *cmd_in);
// void 						ft_execute_path(char *executable, char **tab,

void						ft_print_builtin(char **tab);
void						ft_execute(t_cmd *cmd, t_exec *exec);
void						ft_build_to_parent(t_cmd *cmd, char **tab, int b,
								int in_child);

// CommandLineInterface_utils.c
void						ft_execute_path(t_cmd *cmd, t_exec *exec);
int							check_only_space(char *str);
int							ft_heredoc_in_current_command(t_cmd *cmd);
char						**ft_calloc_cmd_len(t_cmd *cmd);
char						**ft_fill_tab(char **tab, t_cmd *cmd);
int							ft_cmd_size(t_cmd *cmd);

// Pipehandler.c

void						ft_handle_pipes(t_redirect_in *cmd_in,
								t_exec *exec);

// Free utils

void						ft_free_table(char **table);
void						ft_free_nodes(t_node **lst);
// void						ft_free_cmds(t_cmd *cmd);
void						ft_free_cmds(t_cmd **cmd);

// Redirection Handler

t_redirect_in				*ft_open_list_in(t_redirect_in *cmd_in,
								int in_child);
int							ft_redirect_in(t_cmd *cmd, int in_child);
t_redirect_out				*ft_open_list_out(t_redirect_out *cmd_out);
int							ft_redirect_out(t_cmd *cmd);

// Execution Utils

int							is_builtin(char **tab);
void						ft_exit_child(void);
void						ft_error_arg(void);

// Execute builtins in childs

void						ft_exec_echo(t_cmd *cmd, t_exec *exec, int out);
void						ft_exec_export(t_cmd *cmd, t_exec *exec, int out);
void						ft_exec_pwd(t_cmd *cmd, t_exec *exec, int out);
void						ft_exec_env(t_cmd *cmd, t_exec *exec, int out);
void						ft_exec_with_builtin(t_cmd *cmd, t_exec *exec,
								int out);

// Build_to_parent.c

t_redirect_in				*ft_open_list_in(t_redirect_in *cmd_in,
								int in_child);
int							ft_redirect_in(t_cmd *cmd, int in_child);
void						ft_exec_in(char **tab, int b);
t_redirect_out				*ft_open_list_out(t_redirect_out *cmd_out);
int							ft_redirect_out(t_cmd *cmd);
void						ft_exec_out(char **tab, int b, int out);

// CommandLineInterface.c
int							cli(void);
void						pwd(void);
int							cd(char *cmd);
void						exit_err(int errnum);
void						ft_error(void);

// input_tokenizer.c
int							ft_find_pair(char *str, char c);
void						ft_replace_by_space(char *str, int len, char c);
void						ft_trim_spaces(char *str);
int							ft_token_len(const char *s, int c);
int							ft_handle_quotes(char *str);

// command_parser
typedef enum s_token_type
{
	WORD = 1,
	SINGLE_QUOTE = 2,
	DOUBLE_QUOTE = 3,
	REDIRECT_IN = 4,
	REDIRECT_OUT = 5,
	REDIRECT_HEREDOC = 6,
	REDIRECT_APPEND = 7,
	PIPE = 8,
	INVALID = 9
}							t_type;

t_node						*ft_tokenize(char *rl);
t_cmd						*ft_parse(t_node *head);
t_type						get_type_token(char *rl);
t_node						*ft_stack_new(char *str, int return_value);
void						ft_add_back(t_node **list, t_node *new);

// builtins
void						builtin_cd(int fd, char *s);
int							home_not_set_check(void);
int							oldpwd_not_set_check(void);
char						*pwd_return_set_old(void);
void						builtin_echo(char **strs, int fd);
void						builtin_pwd(int fd);
void						builtin_export(int fd, char **strs);
void						builtin_unset(char **strs);
void						builtin_env(int fd);
void						builtin_exit(int fd, char **strs);
t_redirect_in				*ft_open_list_in(t_redirect_in *cmd_in,
								int in_child);
t_redirect_in				*ft_lastin(t_redirect_in *list);
t_redirect_in				*ft_new_in(t_node *node);
void						ft_add_in(t_cmd *list, t_redirect_in *new);
t_redirect_out				*ft_open_list_out(t_redirect_out *cmd_out);
t_redirect_out				*ft_lastout(t_redirect_out *list);
t_redirect_out				*ft_new_out(t_node *node);
void						ft_add_out(t_cmd *list, t_redirect_out *new);
t_cmd						*ft_add_cmd(t_cmd *cmd_list, t_cmd *new);
t_cmd						*ft_lastcmd(t_cmd *list);
void						ft_fill_word_or_quote(t_node *node,
								t_cmd *current_cmd);
void						ft_fill_redirection(t_node *node,
								t_cmd *current_cmd);
t_cmd						*ft_create_command(t_node **node, t_cmd *cmd_list);
t_cmd						*ft_parse(t_node *head);
t_cmd						*ft_new_cmd(void);
int							ft_grammar_check(t_node *head);

// Main.c
typedef struct s_shell
{
	struct s_env			*env_lst;
	int						exit_status;
	char					*rl;
	char					*pwd;
	int						sig_c;
	int						shlvl;
	int						shlvl_allowed;
}							t_shell;

#endif