/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SignalHandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:21:20 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/02 13:46:13 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	signal_handler_child(int sigtype)
{
	int		status;
	int		pid_stat;
	int		shell_lvl;
	char	*shell_lvl_str;

	pid_stat = 1;
	if (sigtype == SIGCHLD)
	{
		if (search_value_env_lst("SHLVL") != NULL && g_shell.shlvl_allowed == 0)
		{
			shell_lvl = ft_atoi(search_value_env_lst("SHLVL")) + 1;
			shell_lvl_str = ft_itoa(shell_lvl);
			edit_env_lst(&g_shell.env_lst, "SHLVL", shell_lvl_str);
			free(shell_lvl_str);
		}
		while (pid_stat > 0)
			pid_stat = waitpid(-1, &status, WNOHANG);
		if (search_value_env_lst("SHLVL") != NULL && g_shell.shlvl_allowed == 0)
		{
			shell_lvl_str = ft_itoa(shell_lvl - 1);
			edit_env_lst(&g_shell.env_lst, "SHLVL", shell_lvl_str);
			free(shell_lvl_str);
		}
		g_shell.exit_status = WEXITSTATUS(status);
	}
}

void	signal_handler_default(int sigtype)
{
	if (sigtype == SIGINT)
	{
		if (wait3(NULL, WNOHANG, NULL) != -1)
			write(1, "\n", 1);
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_shell.sig_c = 1;
	}
}

void	signal_to_default_behaviour(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		perror("signal");
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		perror("signal");
}

void	initiliaze_signal(void)
{
	struct sigaction	sa_default;
	struct sigaction	sa_ignore;

	sa_default.sa_handler = signal_handler_default;
	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = SA_RESTART;
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	if (sigaction(SIGINT, &sa_default, NULL) == -1)
		perror("sigaction");
	if (sigaction(SIGQUIT, &sa_ignore, NULL) == -1)
		perror("sigaction");
	if (signal(SIGCHLD, signal_handler_child) == SIG_ERR)
		perror("signal");
}
