/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarreto <mbarreto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:19:23 by francisco         #+#    #+#             */
/*   Updated: 2023/06/29 18:08:01 by mbarreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* libraries */

// readline and printf
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// malloc and free
# include <stdlib.h>

// write and usleep
# include <unistd.h>

// waitpid
# include <sys/types.h>
# include <sys/wait.h>

// open
# include <fcntl.h>

// signal
# include <signal.h>

// errno
# include <errno.h>

/* strings & values */

# define PROMPT "Minishell-> "
# define BUFFER_SIZE 42

/* structs */

typedef struct t_ints {
	int		i;
	int		j;
	int		k;
	int		l;
	char	*tmp;
}	t_ints;

typedef struct t_builtins {
	int		echo;
	int		cd;
	int		pwd;
	int		export;
	int		unset;
	int		env;
	int		exit;
}	t_builtins;

typedef struct t_token {
	char	*token;
	int		f_pipe;
	int		f_r_in;
	int		f_r_out;
	int		f_file;
	int		f_singlequotes;
	int		f_doublequotes;
	int		f_dollarsign;
	int		f_envvar;
	int		f_command;
	int		f_flag;
	int		f_builtin;
	int		f_builtins[7];
}	t_token;

typedef struct t_data {
	char	**env;
	char	**paths;
	int		num_commands;
	int		flag_builtin;
	int		old_fd;
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	*pid;
	t_token	*tokens;
}	t_data;

typedef struct t_env {
	char	**env;
	int		status;
}	t_env;

typedef struct t_cmd	t_cmd;

typedef struct t_cmd {
	int		outfd;
	int		infd;
	char	*path;
	char	**args;
	t_cmd	*next;
}	t_cmd;

typedef struct t_signal {
	int		exit_status;
}	t_signal;

/* globals */

extern int	g_exitvalue;

/* sources */

// main.c TESTING
void		print_array(char **arr);
void		print_tokens(t_data **d, char **tokens);

// builtins2.c
int			built_check_unset(char **tokens, char **env, int i);
int			built_unset(char **tokens, t_env *env);
int			built_export(char **tokens, t_env *env, int outfd);

// builtin_utils_2.c
int			is_num(char *str);
void		export_print(char **env, int out);

// builtin_utils_3.c
int			check_var_exist(char *str, char **env);
int			ft_len(char **env);
int			handle_new_var(char **tokens, t_env *env, int i);

// builtin_utils.c
int			is_valid(char *str);
int			strrlen(char *str, char c);
int			env_set(char **tokens, t_env *env, int i);
char		*get_var(char **env, char *envid);
int			var_set(char **tokens);

// builtin.c
int			env_change(t_env *env);
int			built_cd(char **tokens, t_env *env);
int			built_exit(char **tokens, t_env *env);
int			exec_builtin(char **tokens, int outfd);

// command_handling_utils_2.c
void		remove_quotes_2(t_data **d, t_ints *n, t_ints *m, char quotes);
void		get_cmd_2(t_data **d, t_ints *n, t_ints *m, char ***cmd);

// command_handling_utils.c
char		*remove_quotes(t_data **d, t_ints *n, char quotes);
void		skip_redir(t_data **d, t_ints *n);
char		**get_cmd(t_data **d, t_ints *n);
int			get_pwd(t_data **d, char **pwd);

// command_handling.c
t_cmd		*add_cmd(t_cmd *cmd);
void		handle_builtin_cmd(char **tokens);
void		handle_single_cmd(t_data **d);
void		run_cmd(t_data **d, t_ints *n, char ***cmds);
void		handle_multiple_cmds(t_data **d);

// minishell_split_utils.c
int			check_quote(t_ints *n, char *line, char quote);
int			check_command(t_ints *n, char *line);
void		get_quote_len(t_ints *n, char *line, char quote);
void		get_quote(t_ints *n, char ***tokens, char *line, char quote);

// minishell_split.c
char		**alloc_tokens_array(char *line);
int			alloc_tokens_strings(char ***tokens, char *line);
void		fill_tokens(char ***tokens, char *line, int token_num);
char		**ft_minishell_split(char *line);

// parsing_utils_2.c
int			check_char(char c);
char		**get_variable(t_data **d, t_ints *n);
char		**get_values(char **vars);
int			get_calloc_size(t_data **d, t_ints *n, \
			char **vars, char **vars_values);
void		expand_variable(t_data **d, t_ints *n);

// parsing_utils.c
int			try_paths(t_data **d, t_ints *n, int i);
int			check_for_command(t_data **d, t_ints *n);
void		run_checks(t_data **d, t_ints *n);
void		run_checks_quotes(t_data **d, t_ints *n);

// parsing.c
void		fill_tokens_struct(t_data **d, char **tokens);
int			fill_flags(t_data **d, t_ints *n, int builtin);
int			check_for_builtin(t_data **d, t_ints *n);
void		sort_tokens(t_data **d, char **tokens);
int			parse_command(t_data *d, char *line);

// pipes.c
void		get_index(t_data **d, t_ints *n);
void		check_for_redirs(t_data **d, t_ints *n, \
			int *f_input, int *f_output);
void		close_pipe(t_data **d);
void		handle_pipes(t_data **d, t_ints *n);

// redirect_2.c
void		redirect_input(t_data **d, t_ints *n, char *redir);
void		redirect_output(t_data **d, t_ints *n, char *redir);

// redirect.c
char		*skip_quotes(t_data **d, t_ints *n);
void		handle_heredoc(t_data **d, char *delimiter);
void		handle_redirections(t_data **d, t_ints *n, char *redir);
void		check_redir(t_data **d, int cmd_num);

// signals.c
t_signal	*sig_func(void);
void		sig_handler(int sig);
void		if_ctrl_d(t_data **d, char *buffer, char *line);

// utils_2.c
t_env		*env_func(void);
char		*shell_lvl(char *envp);
char		**env_create(char **envp);

// utils.c
void		get_paths(t_data **d);
int			get_pipe_num(char *buffer);
void		space_pipes(char *buffer, char **line, int *i, int *j);
char		*sort_line(char *buffer);
void		free_all(t_data **d);

/* functions */

// ft_atoi.c
int			ft_atoi(const char *str);

// ft_calloc.c
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);

// ft_isalnum.c
int			ft_isalnum(char c);

// ft_itoa_2.c
char		*rev_num(char *num);
void		put_num(int n, char *num);
char		*ft_itoa_2(int n);

// ft_itoa.cfree(comando);
char		*ft_itoa(char *str, int *maxdig, int count, int n);

// ft_split.c
int			mem_size(char const *s, char c);
int			word_size(const char *s, char c);
char		**fill_strs(char **strs, const char *s, char c);
char		**ft_split(char const *s, char c);

// ft_strarr_cpy.c
char		**ft_strarr_copy(char **arr);

// ft_strarr_free.c
void		ft_strarr_free(char **array);

// ft_strchr.c
char		*ft_strchr(const char *s, int c);

// ft_strdup.c
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s1);

// ft_strjoin.c
char		*ft_strjoin(char const *s1, char const *s2);

// ft_strlen.c
size_t		ft_strlen(const char *s);

// ft_strncmp.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// get_next_line.c
char		*ft_free(char *buffer, char *buf);
char		*ft_next(char *buffer);
char		*ft_line(char *buffer);
char		*read_file(int fd, char *ret);
char		*get_next_line(int fd);

/* colors */

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"
# define CYAN_B "\033[1;96m"
# define DEFAULT "\033[0m"
# define DEFAULT_B "\033[1;0m"

#endif