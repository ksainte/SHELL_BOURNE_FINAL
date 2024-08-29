/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirect_to_childs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:57:38 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:40:36 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_execute_in_childs(t_cmd *cmd, t_exec *exec)
{
	if (exec->tab[0] != NULL)
		g_shell.shlvl_allowed = ft_strcmp(exec->tab[0], "./minishell");
	if (g_shell.shlvl_allowed == 0)
	{
		if (search_value_env_lst("SHLVL") == NULL)
			add_env_lst(&g_shell.env_lst, "SHLVL", "1");
		else
		{
			g_shell.shlvl = ft_atoi(search_value_env_lst("SHLVL"));
			g_shell.shlvl++;
			if (g_shell.shlvl > 1000 || g_shell.shlvl <= 0)
				g_shell.shlvl = 0;
			edit_env_lst(&g_shell.env_lst, "SHLVL", ft_itoa(g_shell.shlvl));
		}
	}
	exec->is_in_child = 1;
	ft_execute(cmd, exec);
	if (g_shell.shlvl_allowed == 0)
	{
		g_shell.shlvl--;
		edit_env_lst(&g_shell.env_lst, "SHLVL", ft_itoa(g_shell.shlvl));
	}
}

void	ft_exchange_pipes(t_exec *exec)
{
	close(exec->in_pipe[0]);
	close(exec->in_pipe[1]);
	exec->in_pipe[0] = exec->out_pipe[0];
	exec->in_pipe[1] = exec->out_pipe[1];
}

void	ft_close_pipes(t_exec *exec)
{
	close(exec->out_pipe[0]);
	close(exec->out_pipe[1]);
}

void	ft_current_cmd_table(t_cmd *cmd, t_exec *exec)
{
	free(exec->tab);
	exec->tab = ft_calloc_cmd_len(cmd);
	exec->tab = ft_fill_tab(exec->tab, cmd);
}

void	ft_launch_execution(t_cmd *cmd, t_exec *exec)
{
	int	pid;

	exec->in_pipe[0] = -1;
	if (cmd->next)
		pipe(exec->in_pipe);
	while (cmd)
	{
		if (exec->in_pipe[0] != -1)
			pipe(exec->out_pipe);
		if (exec->i != 0)
			ft_current_cmd_table(cmd, exec);
		pid = fork();
		if (pid == 0)
			ft_execute_in_childs(cmd, exec);
		else if (pid < 0)
			ft_error();
		cmd = cmd->next;
		exec->i++;
		if (exec->in_pipe[0] != -1)
			ft_exchange_pipes(exec);
	}
	if (exec->in_pipe[0] != -1)
		ft_close_pipes(exec);
	while (wait(NULL) != -1)
		continue ;
}
