/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:11:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 05:29:02 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	usage_help_menu(char *option)
{
	if (!ft_strcmp(option, "-h"))
	{
		printf("*************************************************.....******\n");
		printf("                                                 O O  /     \n");
		printf("                                                /<   /      \n");
		printf("                 __   _          ___ __________/_#__=o      \n");
		printf(" ___ ___  __ _  / /  (_)__      /(- /(\\_\\________   \\    \n");
		printf("/_ // _ \\/  ' \\/ _ \\/ / -_)     \\ ) \\ )_      \\o     \\ \n");
		printf("/__/\\___/_/_/_/_.__/_/\\__/      /|\\ /|\\       |'     |    \n");
		printf("       __       ____                          /o   __\\     \n");
		printf("  ___ / /  ___ / / /                         / '     |      \n");
		printf(" (_-</ _ \\/ -_) / /                        /_/\\______|     \n");
		printf("/___/_//_/\\__/_/_/                        (   _(    <       \n");
		printf("                                           \\    \\    \\   \n");
		printf("                                             \\____\\___\\  \n");
		printf("Coded by: hkaddour & akouame                 ____\\_\\___\\ \n");
		printf("                                            |___ |_______|..\n");
		printf("\nUsage\n\trun ./minishell with no args\n");
	}
	else
	{
		printf("minishell: %s: No such argument use -h for help\n", option);
		exit(127);
	}
}

void	process_kill(t_data *data)
{
	printf(MOVE_UP_RIGHRT "\t\texit\n");
	free_data_die_process(data);
	exit(0);
}

void	*allocation(t_data *data, size_t count, size_t size, int chk)
{
	void		*ptr;

	ptr = ft_calloc(count, size);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

char	*add_dup(t_data *data, char *s, int chk)
{
	char	*ptr;

	ptr = ft_strdup(s);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

char	*add_join(t_data *data, char *s, char *s1, int chk)
{
	char	*ptr;

	ptr = ft_strjoin(s, s1);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}
