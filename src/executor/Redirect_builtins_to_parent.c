/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Redirect_builtins_to_parent.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:09:46 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 11:10:04 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd_in_parent(t_cmd *cmd, char **tab, int in_child)
{
	if (cmd->list_in || cmd->list_out)
		ft_build_to_parent(cmd, tab, 4, in_child);
	else
		builtin_cd(1, tab[1]);
}

void	ft_unset_in_parent(t_cmd *cmd, char **tab, int in_child)
{
	if (cmd->list_in || cmd->list_out)
		ft_build_to_parent(cmd, tab, 5, in_child);
	else
		builtin_unset(tab);
}

void	ft_env_in_parent(t_cmd *cmd, char **tab, int in_child)
{
	if (cmd->args)
		ft_error();
	else if (cmd->list_in || cmd->list_out)
		ft_build_to_parent(cmd, tab, 3, in_child);
	else
		builtin_env(1);
}

void	ft_echo_in_parent(t_cmd *cmd, char **tab, int in_child)
{
	if (cmd->list_in || cmd->list_out)
		ft_build_to_parent(cmd, tab, 1, in_child);
	else
		builtin_echo(tab, 1);
}

void	ft_export_in_parent(t_cmd *cmd, char **tab, int in_child)
{
	if (cmd->list_in || cmd->list_out)
		ft_build_to_parent(cmd, tab + 1, 2, in_child);
	else
		builtin_export(1, tab + 1);
}
