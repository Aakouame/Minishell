/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:24:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 04:25:59 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define LL_MAX "9223372036854775807"
# define LL_MIN "-9223372036854775808"

typedef enum types
{
	WRD,
	W_SPACE,
	PIPE,
	S_QUOT,
	D_QUOT,
	DOLLA,
	O_TRNC,
	O_APEND,
	I_TRNC,
	I_APEND,
}	t_types;

typedef struct s_env
{
	char			*sec;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct token
{
	t_types			type;
	char			*value;
	struct token	*next;
}	t_token;

typedef struct s_red
{
	t_types			typ;
	char			*file;
	char			*determiner;
	struct s_red	*next;
}	t_red;

typedef struct cmd
{
	char		**cmd;
	t_red		*redirect;
	int			f_in;
	int			f_out;
	int			*tab_pipe;
	int			hrdoc_fd;
	struct cmd	*next;
}	t_cmd;

typedef struct s_free
{
	void			*value;
	struct s_free	*next;
}	t_free;

typedef struct s_data
{
	int			i;
	int			j;
	int			hrdoc_delimiter_dolla;
	int			exp_len;
	int			qot_aftr_dolla;
	int			tokn_hrdoc;
	int			i_line;
	int			chk_hrdoc;
	int			chk_dolla;
	int			chk_q_hrdoc;
	int			hrdoc_fd[2];
	int			chk_hrdoc_exit;
	int			error_lexer;
	int			size_cmd;
	int			old_pwd_make;
	int			chk_redct_exist;
	int			chk_export_plus;
	int			tok_len;
	int			hrdoc_len;
	int			chk_hrdc_cls;
	char		*pwd_of_mysys;
	char		**env_exec;
	char		*old_pwd_value;
	char		*buff;
	char		*line;
	char		**env;
	char		**args;
	char		*beg_line;
	char		*n_line;
	char		*buff_expnd;
	t_env		*l_env;
	t_cmd		*v_cmd;
	t_cmd		*trav_cmd;
	t_free	*p_die;
	t_free	*p_running;
	t_token	*t_join;
	t_token	*trav;
	t_token	*t_token;
}	t_data;

/******* Function of tokenizer *********/
char	*expand_the_value(t_data *data, char *value);
int		expand_len(t_data *data, char *value);
int		ft_acceptable_char(int c);
void	parser_phase(t_data *data);
void	init_var_tokenizer(t_data *data);
void	tokenizer(t_data *data);

/******* Function of tokenizer token identifier *********/
void	dup_from_addr_to_other(char *ptr, char *begin, char *end);
void	token_linker(t_data *data, t_token *trav);
int	unacceptable_token(t_data *data, char c);
int	is_pipe(t_data *data, char *n_line);
int	is_space(t_data *data, char *n_line);
int	is_i_redirection(t_data *data, char *n_line);
int	is_o_redirection(t_data *data, char *n_line);
int	is_dolla(t_data *data, char *n_line);
int	is_s_quote(t_data *data, char *n_line);
int	is_d_quote(t_data *data, char *n_line);
int	is_word(t_data *data, char *n_line);

/******* Function of join token ************/
void	allocate_join_token(t_data *data);
void	join_t_token(t_data *data);

/******* Function of lexer ************/
int	lexer_pt2(t_data *data);
int	word_lexer(char *token);
int	pipe_lexer(char *token);
int	quotes_lexer(char quote, char *token);
int	redirection_lexer(char redirect, char *token);


/******* Function of parser ************/
void	heredoc_implement(t_data *data, char *det);
void	allocate_red_node(t_data *data, int red_len);
void	allocate_cmd_node(t_data *data);
t_token	*init_var_get_cmd_parsing(t_data *data, int *i, int *red, int *cmd);
int		count_cmd(t_data *data);
void	parsing_get_len_alloc_cmd_arr(t_data *data, int *len, int *red_len);
void	parser(t_data *data);


/**** Function of one_cmd execution ****/
void	close_fds_of_pipeline(t_cmd *trav);
int		pipeline_helper(t_data *data);
int		plug_pipes_in_node(t_data *data);
void	error_close_pipes(t_data *data);
void	pipeline_parent(t_data *data);
void	pipeline(t_data *data);
void	check_if_x_ok(t_data *data, t_cmd *cmd, char *path);
void  fds_closer(t_cmd *cmd, t_red *red);
void  run_one_cmd(t_data *data);
void  exit_status(int *exit_stat, int status);
int		find_slash(char *cmd);
int		check_redirection(t_data *data, t_cmd *cmd);
void  run_one_cmd(t_data *data);
void  execute_sys_cmd(t_data *data, t_cmd *cmd);
void  execution(t_data *data);


/**** Function of builtin cmd **********/
void	free_sp(t_data *data, char **sp);
void	cd_cmd(t_data *data, t_cmd *node);
void	echo_cmd(t_data *data, t_cmd *trav);
void  pwd_cmd(t_data *data);
void	env_cmd(t_data *data, t_cmd *cmd);
void	export_cmd(t_data *data, t_cmd *trav_c);
void	unset_cmd(t_data *data, t_cmd *trav_c);
void	exit_cmd(t_data *data, t_cmd *trav);
int		check_builtin(t_data *data, char **cmd);
void	builtin_cmd(t_data *data, t_cmd *node);


/**** Function of cd **********/
void  cd_between_pwd_and_oldpwd(t_data *data, char *cmd);
void  cd_everywhere_at_once(t_data *data, char *cmd);
void  change_oldpwd(t_data *data);
void  change_pwd(t_data *data, char *path);
void  old_pwd_alloc(t_data *data);
void	execute_cd_swap_init(t_data *data, t_env **pwd, t_env **old);


/**** Function of env **********/
void	env_shlvl_helper(t_data *data, t_env *env);
void  sort_env(t_data *data);
t_env	*getenv_addr(t_data *data, char *sec);
void	env_double_ptr(t_data *data);
void  get_env(t_data *data);


/**** Function of export **********/
int 	check_export_error(t_data *data, char *cmd);
int 	if_exist_or_not(t_data *data, char *cmd);
int 	check_if_equal_or_wrd(char *cmd);
int 	dup_opt_wrd(t_data *data, t_env *env, char *cmd);
int 	check_existence(t_data *data, char *cmd, int hold, t_env *env);
void  dup_opt_equal_helper(t_env **env, char *cmd, int *hold);


/**** Function of exit *************/
int	check_if_llong_helper(char *nbr, int *index, char **ll);


/******* Function of free *********/
void	free_data_running_process(t_data *data, int chk);
void	free_data_die_process(t_data *data);
void	add_node_p_running(t_data *data, void *addr);
void	add_node_p_die(t_data *data, void *addr);


/******* Function of shell *********/
void	process_kill(t_data *data);
void	init_shell_elem(t_data *data, char **av, char **env);
void	*allocation(t_data *data, size_t count, size_t size, int chk);
char	*add_join(t_data *data, char *s, char *s1, int chk);
char	*add_dup(t_data *data, char *s, int chk);
void	sig_c(int c);


/******* Function of error *********/
void	error_alloc(void);
void	error_fork(t_data *data);
void	error_pipe(t_data *data, char *msg);
void	error_cd(t_data *data, char *msg);
void	stdanred_error(char *msg, char *arg, int chk);

#endif
