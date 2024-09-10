/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:24:06 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/10 19:57:35 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(int signum)
{
	(void)signum;
	printf("exit\n");
	exit(0);
}

void	setup_signal_handlers(void)
{
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_eof);
}

void	data_init(t_data *data)
{
	data->line = NULL;
	data->envp = NULL;
	data->exit_status = 0;
	data->envp_list = NULL;
	data->export_list = NULL;
	data->path = NULL;
	data->tokens = NULL;
	data->files = NULL;
	data->cmd = NULL;
}
