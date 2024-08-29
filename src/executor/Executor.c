/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:01:21 by ks19              #+#    #+#             */
/*   Updated: 2024/08/05 17:42:13 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_builtins_in_parent(t_cmd *cmd, char **tab, int in_child)
{
	if (!(ft_strncmp(tab[0], "env", 4)))
		ft_env_in_parent(cmd, tab, in_child);
	else if (!(ft_strncmp(tab[0], "echo", 5)))
		ft_echo_in_parent(cmd, tab, in_child);
	else if (!(ft_strncmp(tab[0], "export", 7)))
		ft_export_in_parent(cmd, tab, in_child);
	else if (!(ft_strncmp(tab[0], "exit", 5)))
	{
		clear_history();
		builtin_exit(1, tab);
	}
}

void	ft_init_var(t_exec *exec, t_cmd *cmd)
{
	exec->i = 0;
	exec->tab = NULL;
	exec->is_heredoc = 0;
	exec->is_in_child = 0;
	exec->cmd_size = ft_cmd_size(cmd);
	exec->tab = ft_calloc_cmd_len(cmd);
	exec->tab = ft_fill_tab(exec->tab, cmd);
	exec->is_heredoc = ft_heredoc_in_current_command(cmd);
}

int	ft_is_builtin(char *str)
{
	if (!(ft_strncmp(str, "env", 4)) || !(ft_strncmp(str, "echo", 5))
		|| !(ft_strncmp(str, "export", 7)) || !(ft_strncmp(str, "exit", 5)))
		return (1);
	return (0);
}

void	ft_execve(t_cmd *cmd)
{
	t_exec	exec;

	ft_init_var(&exec, cmd);
	if (!(ft_strncmp(exec.tab[0], "cd", 3)) && (exec.cmd_size == 1))
		ft_cd_in_parent(cmd, exec.tab, 0);
	else if (!(ft_strncmp(exec.tab[0], "unset", 6)) && (exec.cmd_size == 1))
		ft_unset_in_parent(cmd, exec.tab, 0);
	else if (exec.cmd_size == 1 && exec.is_heredoc == 0
		&& ft_is_builtin(exec.tab[0]))
		ft_builtins_in_parent(cmd, exec.tab, exec.is_in_child);
	else
		ft_launch_execution(cmd, &exec);
	free(exec.tab);
}
