/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:53:03 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 01:55:17 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int count_len_join_token(t_data *data)
{
    t_token *trav;
    int     i;

    i = 0;
    trav = data->t_token;
    while (trav)
    {
        if (trav->type == WRD || trav->type == DOLLA || \
                trav->type == S_QUOT || trav->type == D_QUOT)
        {
            i++;
            while (trav->type == WRD || trav->type == DOLLA || \
                trav->type == S_QUOT || trav->type == D_QUOT)
            {
                trav = trav->next;
                if (!trav)
                    break ;
            }
        }
        else if (trav->type == W_SPACE)
            trav = trav->next;
        else if (trav->type == O_TRNC || trav->type == O_APEND  || \
                trav->type == I_TRNC || trav->type == I_APEND)
        {
            i++;
            if (trav->next->type == W_SPACE)
                trav = trav->next->next;
            else
                trav = trav->next;
            while (trav->type == WRD || trav->type == DOLLA || \
                trav->type == S_QUOT || trav->type == D_QUOT)
            {
                trav = trav->next;
                if (!trav)
                    break ;
            }
        }
        else if (trav->type == PIPE)
        {
            i++;
            trav = trav->next;
        }
    }
    return (i);
}

void    allocate_join_token(t_data *data)
{
    //int i;
    int len;
    j_token *head;
    j_token *node;
    
    //i = 1;
    len = count_len_join_token(data) - 1;
    head = allocation(data, 1, sizeof(j_token), 1);
    data->t_join = head;
    while (len--)
    {
        node = allocation(data, 1, sizeof(j_token), 1);
        head->next = node;
        head = node;
        //i++;
    }
}

t_token *cpy_data_to_join_token(t_data *data, t_token *trav, j_token *j_trav)
{
    int     len;
    t_token *hold;

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
    j_trav->value = allocation(data, len + 1, sizeof(j_token), 1);
    len = 0;
    while (trav->type == WRD || trav->type == DOLLA || \
        trav->type == S_QUOT || trav->type == D_QUOT)
    {
        if (data->tokn_hrdoc && (trav->type == S_QUOT || trav->type == D_QUOT))
            data->chk_q_hrdoc = 1;
        ft_strlcpy(&j_trav->value[len], trav->value, ft_strlen(trav->value) + 1);
        len += ft_strlen(trav->value);
        trav = trav->next;
        if (!trav)
            break ;
    }
    return (trav);
}

void    join_t_token(t_data *data)
{
    t_token *trav;
    j_token *j_trav;

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
        else if (trav->type == O_TRNC || trav->type == O_APEND  || \
                trav->type == I_TRNC || trav->type == I_APEND)
        {
            j_trav->type = trav->type;
            data->tokn_hrdoc = 1;
            if (trav->next->type == W_SPACE)
                trav = trav->next->next;
            else
                trav = trav->next;
            trav = cpy_data_to_join_token(data, trav, j_trav);
            j_trav = j_trav->next;
        }
        else if (trav->type == PIPE)
        {
            j_trav->type = PIPE;
            j_trav = j_trav->next;
            trav = trav->next;
        }
    }

    //j_trav = data->t_join;
    //while (j_trav)
    //{
    //    printf("%d  ||   %s\n", j_trav->type, j_trav->value);
    //    j_trav = j_trav->next;
    //}
}
