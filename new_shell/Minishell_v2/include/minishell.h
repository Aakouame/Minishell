/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:24:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 03:03:47 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#	include <signal.h>
#	include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define MOVE_UP_RIGHRT "\033[1A\033[12C"
# define CLR1 "\001\e[40m \e[97m \e[44m\e[30m\e[44m \e[30m\002"
# define CLR1ERR "\001\e[103m \e[91m \e[40m\e[93m \e[97m \e[44m\e[30m\e[44m \e[30m\002"
# define CLR2 "\001 \e[0m\e[34m\e[0m \002"
# define LL_MAX "9223372036854775807"
# define LL_MIN "-9223372036854775808"

typedef enum	types
{
	WRD, 			//all words and characters
	W_SPACE, 	// \t and spaces
	PIPE, 		// pipes |
	S_QUOT, 	// ''
 	D_QUOT, 	// ""
	DOLLA, 		// $
	O_TRNC, 	// >
	O_APEND,  // >>
	I_TRNC, 	// <
	I_APEND,  // <<
} t_types;

typedef struct s_env
{
	char	*sec;
	char	*value;
	struct s_env *next;
} t_env;

typedef struct token
{
	t_types type;
	char		*value;
	struct token *next;
} t_token;

typedef struct join_token
{
	t_types type;
	char		*value;
	struct join_token *next;
}	j_token;

typedef	struct s_red
{
	t_types	typ;
	char	*file;
	char	*determiner;
	struct s_red *next;
} t_red;

typedef	struct cmd
{
	char	**cmd;
	t_red	*redirect;
	int		f_in;
	int		f_out;
	int		*tab_pipe;
	int		hrdoc_fd;
	struct cmd	*next;
} t_cmd;

typedef struct die_p
{
	void	*value;
	struct die_p *next;
} d_free;

typedef struct running_p
{
	void	*value;
	struct running_p *next;
} r_free;

typedef struct s_data
{
	//i need another var to check if delimiter is double quote so int heredoc data to not expand
	//new variable
	int		hrdoc_delimiter_dolla; //this one to check if there's a heredoc and should not expand $PWD
	char	*buff_expnd;
	int		exp_len;
	int		qot_aftr_dolla;
	int		tokn_hrdoc; //this one is to show me that im in heredoc in join tokenizer
	j_token	*t_join;
	j_token *trav;

	//*************
	//tokenizer quotes
	int			d_quot;
	int			s_quot;
	char		*line;
	char		**env;
	char		**args;
	char		*beg_line;
	char		*n_line;
	int			i_line;
	int			index;
	int			check;
	int			i;
	int			j;
	int			chk_hrdoc; //this one is for heredoc to check so i can ignore expanding $PWD
	int			chk_dolla; //this one checks for $? so it print or not and change the value in how the process got end
	int			d_q_chk; // this one to check $"HOME"  and "$""HOME" in heredoc
	int			chk_q_hrdoc; //this one to check if the determinater have "" '' so to not expand $ inside the heredoc
	int			hrdoc_fd[2];
	int			chk_hrdoc_exit; //this one check if heredoc got exit with ctrl c so to not finish the other hrdoc << l << d
	t_token	*node;
	//**t_token *trav;
	t_env		*l_env;
	t_types	typ;
	t_token	*t_token;
	//parsing
	t_cmd	*v_cmd;
	t_cmd	*trav_cmd;
	char 	*buff;
	//error of lexer var
	int			error_lexer;
	/*var of execution*/
	int			size_cmd;
	char		*old_pwd_value; //this one is for cd env oldpwd to dup the old path of cd
	int			old_pwd_make;
	int			chk_redct_exist; //var to chk if redirection exist in run_one_cmd
	int			chk_export_plus; //this var is for hey+=kjsdk
	int			status_of_oldpwd;
	char		*pwd_of_mysys; //this one keep my pwd in case if i unset pwd
	/*end of execution*/
	//for prompt
	char		*prompt;
	//env of execve double array pointer
	char		**env_exec;
	//len of tokenizer value
	int			tok_len;
	//count data len of heredoc
	int			hrdoc_len;
	//parsing heredoc to close pipes << l << d close the old one
	int			chk_hrdc_cls;
	//dial free
	d_free	*p_die;
	r_free	*p_running;
	int			s_stdout; //hold dup of 1
}	t_data;

/********* NEW FUNCTION I ADDED ***************/
void	dup_from_addr_to_other(char *ptr, char *begin, char *end);
int		word_lexer(char *token);
int		pipe_lexer(char *token);
int		quotes_lexer(char quote, char *token);
int		redirection_lexer(char redirect, char *token);
char	*allocate_token_value_dollar(t_data *data, char *begin, char *end, int len);
int		count_dollar_beginning(t_data *data, char *token);
int		get_len_dollar_token(t_data *data, char *begin, char *end);
int		add_dollar_beginning(t_data *data, char *dollar_token, char *begin);
char	*expand_the_value(t_data *data, char *value);
int		expand_len(t_data *data, char *value);
void	join_t_token(t_data *data);
j_token	*init_var_get_cmd_parsing(t_data *data, int *i, int *red, int *cmd);







/******* Function of tokenizer *********/
void	parser_phase(t_data *data);
void	init_var_tokenizer(t_data *data);
void	tokenizer(t_data *data);

/******* Function of tokenizer allocate node *********/
int		ft_acceptable_char(int c);
void	arg_after_hrdoc(t_data *data);
void	add_dolla(t_data *data);
int		add_dolla_begin(t_data *data);
void	node_attach(t_data *data);
void	add_d_quote_helper(t_data *data);
int		add_node(t_data *data, t_types typ);

/******* Function of tokenizer count len *********/
void	count_d_quote_helper(t_data *data);
void	count_arg_after_hrdoc(t_data *data);
void	count_dolla(t_data *data);
int		count_dolla_begin(t_data *data);
int		get_len(t_data *data);

/******* Function of tokenizer token identifier *********/
void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ);
int		is_o_redirection(t_data *data, char *n_line);
int		is_i_redirection(t_data *data, char *n_line);
int		is_dolla(t_data *data, char *n_line);
void	is_quote_helper(t_data *data, int c, char *n_line);
int		is_d_quote(t_data *data, char *n_line);
int		is_s_quote(t_data *data, char *n_line);
int		is_pipe(t_data *data, char *n_line);
int		is_space(t_data *data, char *n_line);
void	is_word_helper(t_data *data, char *n_line, int *typ);
int		is_word(t_data *data, char *n_line);

/******* Function of lexer ************/
int	quote_lexer_helper(int s_c, int d, int s, int typ);
int	lexer_pt2(t_data *data);
int	lexer_pt1(t_data *data, t_types typ);
/****************************************************************/


/******* Function of parser ************/
//t_token	*init_var_get_cmd_parsing(t_data *data, int *i, int *red, int *cmd);
void  parsing_get_len_alloc_cmd_arr(t_data *data, int *len, int *red_len);
int		count_cmd(t_data *data);
void	allocate_red_node(t_data *data, int red_len);
void	allocate_cmd_node(t_data *data);
void  parser(t_data *data);
/******* Function of parser heredoc ************/
int		len_hrdoc_data(t_data *data, char *ptr);
void	heredoc_sig(int c);
void	heredoc_dolla_allocate(t_data *data, char *ptr, char *str);
void	heredoc_implement(t_data *data, char *det);
/************************************************/


/**** Function of one_cmd execution ****/
void	pipeline_helper(t_data *data);
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
void	usage_help_menu(char *option);
void	process_kill(t_data *data);
int		hrdoc_with_no_cmd_to_close_fd(t_data *data);
void	init_shell_elem(t_data *data, char **av, char **env);
void	*allocation(t_data *data, size_t count, size_t size, int chk);
char	*add_join(t_data *data, char *s, char *s1, int chk);
char	*add_dup(t_data *data, char *s, int chk);
void	prompt_changer(t_data *data);
void	sig_c(int c);


/******* Function of error *********/
void	error_alloc(void);
void	error_fork(t_data *data);
void	error_pipe(t_data *data, char *msg);
void  error_cd(t_data *data, char *msg);

#endif
