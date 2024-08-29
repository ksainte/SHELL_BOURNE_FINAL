/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_path_in_childs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:56:43 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 10:57:09 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_unleash_execution(t_exec *exec)
{
	char	**newenviron;

	newenviron = env_lst_to_tab(g_shell.env_lst);
	signal_to_default_behaviour();
	if (exec->executable != NULL)
		g_shell.shlvl_allowed = ft_strcmp(exec->executable, "./minishell");
	g_shell.exit_status = execve(exec->executable, exec->tab, newenviron);
	initiliaze_signal();
	perror("execve");
	ft_exit_child();
}

void	ft_exec_without_builtin(t_cmd *cmd, t_exec *exec, int out)
{
	if (exec->in_pipe[0] != -1 && exec->i != exec->cmd_size - 1)
	{
		dup2(exec->out_pipe[1], 1);
		close(exec->out_pipe[1]);
	}
	if (cmd->list_out)
	{
		dup2(out, 1);
		close(out);
	}
	ft_unleash_execution(exec);
}

void	ft_execute_path(t_cmd *cmd, t_exec *exec)
{
	int	out;
	int	in;

	out = -1;
	in = -1;
	if (g_shell.sig_c == 1)
		ft_exit_child();
	if (*exec->tab[0] == '\0')
		exec->executable = "/bin/true";
	if (exec->in_pipe[0] != -1)
		ft_handle_pipes(cmd->list_in, exec);
	if (cmd->list_in)
	{
		in = ft_redirect_in(cmd, exec->is_in_child);
		dup2(in, 0);
		close(in);
	}
	if (cmd->list_out)
		out = ft_redirect_out(cmd);
	if (is_builtin(exec->tab))
		ft_exec_with_builtin(cmd, exec, out);
	ft_exec_without_builtin(cmd, exec, out);
}
