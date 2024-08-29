/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:14:56 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:42:29 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_free_nodes(t_node **lst)
{
	t_node	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(*lst)->type = 0;
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

void	ft_free_args(t_args *cmd_args)
{
	t_args	*tmp;

	if (!cmd_args)
		return ;
	while (cmd_args)
	{
		tmp = (cmd_args)->next;
		free(cmd_args);
		cmd_args = tmp;
	}
}

void	ft_free_list_in(t_redirect_in *cmd_in)
{
	t_redirect_in	*tmp;

	if (!cmd_in)
		return ;
	while (cmd_in)
	{
		tmp = (cmd_in)->next;
		free(cmd_in);
		cmd_in = tmp;
	}
}

void	ft_free_list_out(t_redirect_out *cmd_out)
{
	t_redirect_out	*tmp;

	if (!cmd_out)
		return ;
	while (cmd_out)
	{
		tmp = (cmd_out)->next;
		free(cmd_out);
		cmd_out = tmp;
	}
}

void	ft_free_cmds(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->args)
			ft_free_args((*cmd)->args);
		if ((*cmd)->list_in)
			ft_free_list_in((*cmd)->list_in);
		if ((*cmd)->list_out)
			ft_free_list_out((*cmd)->list_out);
		free(*cmd);
		*cmd = tmp;
	}
}
