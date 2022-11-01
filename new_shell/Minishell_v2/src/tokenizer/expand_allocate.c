/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_allocate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:25:11 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/27 15:43:24 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void check_if_exist_in_env(t_data *data, char *tmp)
{
    t_env   *env;

    env = getenv_addr(data, tmp);
    if (!env)
        return ;
    else
    {
        data->j += ft_strlcpy(&data->buff_expnd[data->j], env->value, ft_strlen(env->value) + 1);
        //data->exp_len += ft_strlen(env->value);
    }
}

static void allocate_expand_dollar(t_data *data, char *value)
{
    char *dollar;
    char *tmp;
    int     j;

    data->i++;
    j = 0;
    if (value[data->i] == '0' || value[data->i] == '?')
    {
        if (value[data->i] == '0')
        {
            data->j += ft_strlcpy(&data->buff_expnd[data->j], ft_strrchr(data->args[0], '/') + 1, \
                ft_strlen(ft_strrchr(data->args[0], '/')));
        }
        else
        {
            tmp = ft_itoa(data->chk_dolla);
            add_node_p_running(data, tmp);
            data->j += ft_strlcpy(&data->buff_expnd[data->j], tmp, ft_strlen(tmp) + 1);
            //data->exp_len += ft_strlen(tmp);
        }
        data->i++;
        return ;
    }
    else if (value[data->i] == '$' || (value[data->i] > '0' && value[data->i] <= '9'))
    {
        data->i++;
        return ;
    }
    else if (value[data->i] == 0)
    {
        if (!data->qot_aftr_dolla)
            data->buff_expnd[data->j++] = '$';
        return ;
    }
    else if (value[data->i] == '\"')
    {
        data->buff_expnd[data->j++] = '$';
        data->buff_expnd[data->j++] = value[data->i++];
    }
    else
    {
        while (value[data->i] && ft_acceptable_char(value[data->i]))
        {
            data->i++;
            j++;
        }
        tmp = allocation(data, j + 1, sizeof(char), 1);
        dup_from_addr_to_other(tmp, &value[data->i - j], &value[data->i]);
        check_if_exist_in_env(data, tmp);
    }
}

char *expand_the_value(t_data *data, char *value)
{
    data->buff_expnd = allocation(data, expand_len(data, value) + 1, sizeof(char), 1);
    //printf("%d\n", data->exp_len);
    data->i = 0;
    data->j = 0;
    while (value[data->i])
    {
        if (value[data->i] == '$')
        {
            allocate_expand_dollar(data, value);
        }
        else
            data->buff_expnd[data->j++] = value[data->i++];
    }
    //printf("%s\n", data->buff_expnd);
    return (0);
}