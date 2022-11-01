/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:52:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/31 22:06:34 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	print_env_of_export(t_env *env)
{
	while (env)
	{
		if (!env->value[0])
			printf("declare -x %s\n", env->sec);
		else
			printf("declare -x %s=\"%s\"\n", env->sec, env->value);
		env = env->next;
	}
}

static int	dup_opt_equal(t_data *data, t_env *env, char *cmd)
{
	int	i;
	int	hold;

	if (data->chk_export_plus == 1)
		hold = ft_strcspn(cmd, "+");
	else
		hold = ft_strcspn(cmd, "=");
	if (check_existence(data, cmd, hold, env))
		return (0);
	env->sec = allocation(data, hold + 1, sizeof(char), 0);
	dup_opt_equal_helper(&env, cmd, &hold);
	i = 0;
	env->value = allocation(data, ft_strlen(&cmd[hold]) + 1, \
			sizeof(char), 0);
	while (cmd[hold])
		env->value[i++] = cmd[hold++];
	return (1);
}

//void	attach_export_node(t_data *data, t_env *head, t_env **trav_e)
//{
//	t_env	*hlp;
//
//	hlp = *trav_e;
//	//if (trav_e)
//	if (hlp)
//	{
//		//trav_e->next = head;
//		//trav_e = trav_e->next;
//	}
//	else
//	{
//		data->l_env = head;
//		hlp = head;
//		//data->l_env = head;
//		//trav_e = head;
//	}
//}

static void	export_cmd_helper(t_data *data, t_env **trav_e, \
		t_cmd *trav_c, int i)
{
	int		chk;
	t_env	*head;

	head = 0;
	if (!check_export_error(data, trav_c->cmd[i]))
	{
		chk = if_exist_or_not(data, trav_c->cmd[i]);
		if (chk == 1)
			head = allocation(data, 1, sizeof(t_env), 0);
		if (!check_if_equal_or_wrd(trav_c->cmd[i]))
			chk = dup_opt_wrd(data, head, trav_c->cmd[i]);
		else
			chk = dup_opt_equal(data, head, trav_c->cmd[i]);
		if (chk == 1)
		{
			if (trav_e[0])
			{
				trav_e[0]->next = head;
				trav_e[0] = trav_e[0]->next;
			}
			else
			{
				data->l_env = head;
				trav_e[0] = head;
			}
		}
	}
	else
	{
		data->chk_dolla = 1;
		dup2(data->s_stdout, STDOUT_FILENO);
		printf("minishell: export: '%s': not a valid identifier\n", \
				trav_c->cmd[i]);
		close(data->s_stdout);
	}
}

void	export_cmd(t_data *data, t_cmd *trav_c)
{
	int		i;
	t_env	*trav_e;

	i = 1;
	trav_e = data->l_env;
	if (!trav_c->cmd[i])
		print_env_of_export(trav_e);
	else
	{
		if (trav_e)
		{
			while (trav_e->next)
				trav_e = trav_e->next;
		}
		while (trav_c->cmd[i])
		{
			data->chk_export_plus = 0;
			export_cmd_helper(data, &trav_e, trav_c, i);
			i++;
		}
	}
	sort_env(data);
}
