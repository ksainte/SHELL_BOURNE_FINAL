/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute_in_parent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:04:00 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:50:21 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_exec_in(char **tab, int builtin_type)
{
	if (builtin_type == 1)
		builtin_echo(tab, 1);
	else if (builtin_type == 2)
		builtin_export(1, tab);
	else if (builtin_type == 3)
		builtin_env(1);
	else if (g_shell.sig_c == 0 && builtin_type == 4)
		builtin_cd(1, tab[1]);
	else if (g_shell.sig_c == 0 && builtin_type == 5)
		builtin_unset(tab);
}

void	ft_exec_out(char **tab, int builtin_type, int out)
{
	if (builtin_type == 1)
		builtin_echo(tab, out);
	else if (builtin_type == 2)
		builtin_export(out, tab);
	else if (builtin_type == 3)
		builtin_env(out);
	else if (builtin_type == 4)
		builtin_cd(1, tab[1]);
	else if (builtin_type == 5)
		builtin_unset(tab);
	close(out);
}

void	ft_build_to_parent(t_cmd *cmd, char **tab, int builtin_type,
		int in_child)
{
	int	in;
	int	out;

	in = 0;
	if (cmd->list_in)
	{
		in = ft_redirect_in(cmd, in_child);
		if (!cmd->list_out && in != -1)
			ft_exec_in(tab, builtin_type);
	}
	if (cmd->list_out && in != -1)
	{
		out = ft_redirect_out(cmd);
		ft_exec_out(tab, builtin_type, out);
	}
}
