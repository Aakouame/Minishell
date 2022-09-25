/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/23 13:33:01 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ)
{
	data->typ = typ;
	data->n_line = n_line;
	data->i_line = i;
	data->index += i;
}

static int	is_pipe(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '|')
		return (0);
	while (n_line[i] == '|')
		i++;
	ft_init_tokenizer(data, &n_line[i], i, PIPE);
	return (1);
}

static int	is_space(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != ' ' && !(n_line[i] >= 9 && n_line[i] <= 13))
		return (0);
	while (n_line[i] == ' ' || (n_line[i] >= 9 && n_line[i] <= 13))
		i++;
	ft_init_tokenizer(data, &n_line[i], i, W_SPACE);
	return (1);
}

//here for example okay'ckj' should be in one arg
static int	is_word(t_data *data, char *n_line)
{
	char	c;
	char	*sp;
	int		quote;
	int		typ;

	///sp = "<|\">'$ ";
	sp = "<|>$\t\v\r\f ";
	//\t\v\r\f
	data->i = 0;
	quote = 0;
	typ = WRD;
	while (n_line[data->i])
	{
		data->j = 0;
		if (n_line[data->i] == '\"' || n_line[data->i] == '\'')
		{
			c = n_line[data->i];
			if (n_line[0] == c)
			{
				if (c == '\'')
					typ = S_QUOT;
				else if (c == '\"')
					typ = D_QUOT;
			}
			//else
			//	typ = WRD;
			quote++;
			data->i++;
			//while (beg_line[data->i] != ' ')
			while (n_line[data->i])
			{
				//if (n_line[data->i] == '\'' || n_line[data->i] == '\"')
				if (n_line[data->i] == c)
					quote++;
				if ((n_line[data->i] == ' ' || (n_line[data->i] >= 9 && n_line[data->i] <= 13) ||\
							n_line[data->i] == '|' || n_line[data->i] == '>' || n_line[data->i] == '<')\
						&& quote % 2 == 0)
					break ;
				data->i++;
			}
			if (n_line[data->i] == c)
				data->i++;
		}
		while (sp[data->j])
		{
			//if (beg_line[data->i] == sp[data->j] \
			//		&& (sp[data->j] == '\"' || sp[data->j] == '\''))
			if (n_line[data->i] == sp[data->j])
				break ;
			data->j++;
		}
		if (n_line[data->i] == sp[data->j])
			break ;
		data->i++;
	}
	if (data->i == 0)
		return (0);
	ft_init_tokenizer(data, &n_line[data->i], data->i, typ);
	return (1);
}

void	*spaces_first(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 0)
		return (0);
	return (&str[i]);
}

char	*spaces_takeoff(char *str)
{
	int		len;
	char	*ptr;
	int		i;

	if (!str)
		return (0);
	str = spaces_first(str);
	len = ft_strlen(str) - 1;
	if (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
	{
		while (str[len] == ' ' || (str[len] >= 9 && str[len] <= 13))
			len--;
	}
	else
		return (str);
	ptr = malloc(sizeof(char) * len + 2);
	i = 0;
	while (i <= len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

void	tokenizer(t_data *data)
{
	//here maybe i should check all whitespace also in is_space
	//if (data->line[0] == ' ' || (data->line[0]))
	//**data->beg_line = spaces_first(data->line);
		//data->beg_line = ft_strchr(data->line, ' ');
	//strchr it's not working and take off the whitespaces too
	//**else
	//**	data->beg_line = data->line;
	//take off the end spaces
	//data->beg_line = spaces_takeoff(data->beg_line);
	data->beg_line = spaces_takeoff(data->line);
	if (!data->beg_line)
		return ;
	//those var should not be here
	data->index = 0;
	data->check = 1;
	//those two var should init in the main one time init
	data->chk_hrdoc = 0;
	//**data->chk_dolla = 0;
	ft_init_tokenizer(data, data->beg_line, 0, 0);
	//if (!lexer(data))
	//	return ;
	//while (data->line[data->index])
	while (*data->beg_line)
	{
		if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_dolla(data, data->n_line) || \
				is_pipe(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_i_redirection(data, data->n_line) || \
				is_o_redirection(data, data->n_line))
		{
			if (add_node(data, data->typ))
			{
				//double free
				//free_token_node(data);
				return ;
			}
			//also '' "" now is entring in node of wrd
			//before u return u should free the token node and return an error msg with color and print newline prompt
		}
		//if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
		//		is_d_quote(data, data->n_line) || is_dolla(data, data->n_line))
		//	add_node(data, data->typ);
		//if (is_pipe(data, data->n_line) || is_s_quote(data, data->n_line) || \
		//		is_i_redirection(data, data->n_line) || \
		//		is_o_redirection(data, data->n_line))
		//	add_node(data, data->typ);
	}
	//here token pt 2 maybe i will put it in if or not
	if (lexer_pt2(data))
		return ;
	parser(data);

	//here to write the arg that i entred in the nodes
	//**t_token	*trav;

	//**trav = data->t_token;
	//**while (trav)
	//**{
	//**	printf("| %d |\n", trav->type);
	//**	printf("| %s |\n", trav->value);
	//**	printf("\n");
	//**	trav = trav->next;
	//**}
}
