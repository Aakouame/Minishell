/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:53:03 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 04:34:10 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*cpy_data_helper(t_data *data, t_token *trav, \
		t_token *j_trav, int len)
{
	j_trav->value = allocation(data, len + 1, sizeof(t_token), 1);
	len = 0;
	while (trav->type == WRD || trav->type == DOLLA || \
			trav->type == S_QUOT || trav->type == D_QUOT)
	{
		if (data->tokn_hrdoc && (trav->type == S_QUOT || trav->type == D_QUOT))
			data->chk_q_hrdoc = 1;
		ft_strlcpy(&j_trav->value[len], trav->value, \
				ft_strlen(trav->value) + 1);
		len += ft_strlen(trav->value);
		trav = trav->next;
		if (!trav)
			break ;
	}
	return (trav);
}

static t_token	*cpy_data_to_join_token(t_data *data, t_token *trav, \
		t_token *j_trav)
{
	t_token	*hold;
	int		len;

	len = 0;
	hold = trav;
	while (trav->type == WRD || trav->type == DOLLA || \
			trav->type == S_QUOT || trav->type == D_QUOT)
	{
		len += ft_strlen(trav->value);
		trav = trav->next;
		if (!trav)
			break ;
	}
	trav = hold;
	trav = cpy_data_helper(data, trav, j_trav, len);
	return (trav);
}

static t_token	*join_t_token_helper(t_data *data, t_token *trav, \
		t_token **j_trav)
{
	if (trav->type == O_TRNC || trav->type == O_APEND || \
			trav->type == I_TRNC || trav->type == I_APEND)
	{
		j_trav[0]->type = trav->type;
		data->tokn_hrdoc = 1;
		if (trav->next->type == W_SPACE)
			trav = trav->next->next;
		else
			trav = trav->next;
		trav = cpy_data_to_join_token(data, trav, j_trav[0]);
		j_trav[0] = j_trav[0]->next;
	}
	else if (trav->type == PIPE)
	{
		j_trav[0]->type = PIPE;
		j_trav[0] = j_trav[0]->next;
		trav = trav->next;
	}
	return (trav);
}

void	join_t_token(t_data *data)
{
	t_token	*trav;
	t_token	*j_trav;

	trav = data->t_token;
	data->chk_q_hrdoc = 0;
	data->tokn_hrdoc = 0;
	allocate_join_token(data);
	j_trav = data->t_join;
	while (trav)
	{
		if (trav->type == WRD || trav->type == DOLLA || \
				trav->type == S_QUOT || trav->type == D_QUOT)
		{
			j_trav->type = WRD;
			trav = cpy_data_to_join_token(data, trav, j_trav);
			j_trav = j_trav->next;
		}
		else if (trav->type == W_SPACE)
			trav = trav->next;
		else
			trav = join_t_token_helper(data, trav, &j_trav);
	}
}
