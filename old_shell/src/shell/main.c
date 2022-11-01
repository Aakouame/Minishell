/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/29 14:37:25 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	running_process_helper(t_data *data)
{
	if (data->beg_line)
		add_history(data->line);
	free_data_running_process(data, 1);
}

void	running_process(t_data *data)
{
	t_cmd	*cmd;

	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sig_c);
		signal(SIGQUIT, SIG_IGN);
		//prompt_changer(data);
		//data->line = readline(data->prompt);
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
	else if (ac == 2)
		usage_help_menu(av[1]);
	else
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		exit(127);
	}
	return (0);
}
