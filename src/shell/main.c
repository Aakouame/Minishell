/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 03:30:35 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	running_process_helper(t_data *data)
{
	if (data->beg_line)
		add_history(data->line);
	free_data_running_process(data, 1);
}

static void	running_process(t_data *data)
{
	t_cmd	*cmd;

	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sig_c);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline("$Minishell> ");
		if (!data->line)
			process_kill(data);
		tokenizer(data);
		if (!data->beg_line)
		{
			free_data_running_process(data, 1);
			continue ;
		}
		if (!data->error_lexer)
		{
			env_double_ptr(data);
			execution(data);
		}
		running_process_helper(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac == 1)
	{
		init_shell_elem(&data, av, envp);
		running_process(&data);
	}
	else
	{
		stdanred_error(": No such file or directory\n", av[1], 2);
		exit(127);
	}
	return (0);
}
