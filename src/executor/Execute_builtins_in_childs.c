/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_builtins_in_childs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:55:07 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:40:22 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_exec_echo(t_cmd *cmd, t_exec *exec, int out)
{
	if (cmd->list_out)
	{
		builtin_echo(exec->tab, out);
		close(out);
		ft_exit_child();
	}
	else if (exec->i == exec->cmd_size - 1)
	{
		builtin_echo(exec->tab, 1);
		ft_exit_child();
	}
	else
	{
		builtin_echo(exec->tab, exec->out_pipe[1]);
		close(exec->out_pipe[1]);
		ft_exit_child();
	}
}

void	ft_exec_export(t_cmd *cmd, t_exec *exec, int out)
{
	if (cmd->list_out)
	{
		builtin_export(out, exec->tab + 1);
		close(out);
		ft_exit_child();
	}
	else if (exec->i == exec->cmd_size - 1)
	{
		builtin_export(1, exec->tab + 1);
		close(1);
		ft_exit_child();
	}
	else
	{
		builtin_export(exec->out_pipe[1], exec->tab + 1);
		close(exec->out_pipe[1]);
		ft_exit_child();
	}
}

void	ft_exec_pwd(t_cmd *cmd, t_exec *exec, int out)
{
	if (cmd->list_out)
	{
		builtin_pwd(out);
		close(out);
		ft_exit_child();
	}
	else if (exec->i == exec->cmd_size - 1)
	{
		builtin_pwd(1);
		close(1);
		ft_exit_child();
	}
	else
	{
		builtin_pwd(exec->out_pipe[1]);
		close(exec->out_pipe[1]);
		ft_exit_child();
	}
}

void	ft_exec_env(t_cmd *cmd, t_exec *exec, int out)
{
	if (cmd->list_out && !cmd->args)
	{
		builtin_env(out);
		close(out);
		ft_exit_child();
	}
	else if (exec->i == exec->cmd_size - 1 && !cmd->args)
	{
		builtin_env(1);
		close(1);
		ft_exit_child();
	}
	else if (!cmd->args)
	{
		builtin_env(exec->out_pipe[1]);
		close(exec->out_pipe[1]);
		ft_exit_child();
	}
	else
		ft_error_arg();
}

void	ft_exec_with_builtin(t_cmd *cmd, t_exec *exec, int out)
{
	if (!(ft_strncmp(exec->tab[0], "echo", 5)))
		ft_exec_echo(cmd, exec, out);
	else if (!(ft_strncmp(exec->tab[0], "export", 7)))
		ft_exec_export(cmd, exec, out);
	else if (!(ft_strncmp(exec->tab[0], "pwd", 4)))
		ft_exec_pwd(cmd, exec, out);
	else if (!(ft_strncmp(exec->tab[0], "env", 4)))
		ft_exec_env(cmd, exec, out);
	else if (!(ft_strncmp(exec->tab[0], "unset", 6)))
		ft_exit_child();
	else if (!(ft_strncmp(exec->tab[0], "cd", 3)))
		ft_exit_child();
}
