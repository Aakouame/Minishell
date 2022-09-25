/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:24:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/25 10:54:09 by hkaddour         ###   ########.fr       */
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
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
//# include "~/.brew/opt/readline/include/readline"
//# include "../.brew/opt/readline/include/readline/readline.h"
//# include "../.brew/opt/readline/include/readline/rlstdc.h"
//# include "../.brew/opt/readline/include/readline/rlconf.h"

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

//typedef	struct cmd_detail
//{
//	t_types	typ;
//	char		**cmd;
//	char		*file;
//	//take the typ off and make a struct of redirection file name and type and file name 
//	//maybe add a << stop char *
//	struct s_cmd	*next;
//} d_cmd;
//
//typedef	struct valid_cmd
//{
//	d_cmd	*cmd;
//	int		fd_in;
//	int		fd_out;
//	struct valid_cmd	*next;
//} v_cmd;



//those struct for parsing
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
	struct cmd	*next;
} t_cmd;
//******

//i don't need this one anymore
typedef struct grab_line
{
	char	*ptr;
	char	*tmp;
	char	*buff;
	char	*line;
}	t_gnl;

typedef struct s_data
{
	char		**path;
	char		*line;
	char		**env;
	char		**args;
  char  	*w_path;
	char		**split;
	char		**cmd;
	char		*abs_path;
	char		*beg_line;
	char		*n_line;
	int			i_line;
	int			index;
	char		*var;
	char		*cd_path;
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
  t_token *trav;
	t_env		*shlvl_ptr;
	t_env		*var_exist;
	t_env		*l_env;
	//of derection
	t_token	*built_cmd;
	t_types	typ;
	//dial pipe
	t_token	*trav_p;
	//dial redirection
	t_token	*trav_r;
	t_token	*t_token;
	//parsing
	t_cmd	*v_cmd;
	t_cmd	*trav_cmd;
	//v_cmd		*valid_cmd;
	//d_cmd		*data_cmd;
	//char		**split_cmd;
	/*var of execution*/
	int			size_cmd;
	char		*old_pwd_value; //this one is for cd env oldpwd to dup the old path of cd
	int			old_pwd_make;
	int			chk_redct_exist; //var to chk if redirection exist in run_one_cmd
	int			chk_export_plus; //this var is for hey+=kjsdk
	/*end of execution*/
	//for prompt
	char *prompt;
}	t_data;

/******* Function of tokenizer *********/
void	free_token_node(t_data *data);
int		add_dolla_begin(t_data *data);
//void	add_dolla_begin(t_data *data);
void	add_dolla(t_data *data);
int		add_node(t_data *data, t_types typ);
int		ft_acceptable_char(int c);
void	is_quote_helper(t_data *data, int c, char *n_line);
void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ);
int		is_o_redirection(t_data *data, char *n_line);
int		is_i_redirection(t_data *data, char *n_line);
int		is_s_quote(t_data *data, char *n_line);
int		is_dolla(t_data *data, char *n_line);
int		is_d_quote(t_data *data, char *n_line);
void	tokenizer(t_data *data);

/******* Function of lexer ************/
//int	lexer(t_data *data, t_types typ);
int	lexer_pt2(t_data *data);
int	lexer_pt1(t_data *data, t_types typ);

/******* Function of parser ************/
int		ft_strcmp(const char *s1, const char *s2);
void	heredoc_implement(t_data *data, char *det);
void  parser(t_data *data);

/**** Function of execution **********/
void  execution(t_data *data);

/**** Function of builtin cmd **********/
//void  builtin_cmd(t_data *data, char *cmd);
int		check_builtin(char **cmd);
void  builtin_cmd(t_data *data, char *cmd);
void  cd_cmd(t_data *data);
void  get_env(t_data *data);
void  env_cmd(t_data *data);
void  pwd_cmd(t_data *data);
void  exit_cmd(t_data *data);
void  echo_cmd(t_data *data);
void  export_cmd(t_data *data);
void  unset_cmd(t_data *data);
t_env *node_allocate(void);
char	**env_double_ptr(t_data *data);
//void  cd_cmd(t_data *data);

//this one in the main but should go to cd
void  prompt_changer(t_data *data);


//i gotta sperate the function prototype
//**t_env *node_allocate(t_data *data);
//**void  export_cmd(t_data *data);
//**void  reinit_env(t_data *data);
//**void  echo_cmd(t_data *data);
//**void  env_cmd(t_data *data);
//**void  pwd_cmd(t_data *data);
//**void  get_env(t_data *data);
//**void  error(char *msg, int check);
//**void  lexer(t_data *data);
//**void  tokenizer(t_data *data);
//**void  unset_cmd(t_data *data);
void  nl(void);
//int		ft_acceptable_char(int c);

//**
void  token_s_quote(t_data *data);
//char  *grab_line(int fd);

#endif
