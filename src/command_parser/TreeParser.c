/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeParser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:10:41 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 14:24:29 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_in(t_cmd *list, t_redirect_in *new)
{
	if (!(list->list_in))
		list->list_in = new;
	else
		(ft_lastin(list->list_in))->next = new;
}

void	ft_fill_redirection(t_node *node, t_cmd *current_cmd)
{
	if (node->type == 5 || node->type == 7)
	{
		ft_add_out(current_cmd, ft_new_out(node));
	}
	else
	{
		ft_add_in(current_cmd, ft_new_in(node));
	}
}

t_cmd	*ft_create_command(t_node **node, t_cmd *cmd_list)
{
	t_cmd	*current_cmd;

	cmd_list = ft_add_cmd(cmd_list, ft_new_cmd());
	current_cmd = ft_lastcmd(cmd_list);
	while (*node && (*node)->type != 8)
	{
		if ((*node)->type >= 1 && (*node)->type <= 3)
		{
			ft_fill_word_or_quote(*node, current_cmd);
		}
		else if ((*node)->type >= 4 && (*node)->type <= 7)
		{
			ft_fill_redirection(*node, current_cmd);
			*node = (*node)->next;
		}
		*node = (*node)->next;
	}
	return (cmd_list);
}

t_cmd	*ft_parse(t_node *head)
{
	t_cmd	*command_list;

	if (!(ft_grammar_check(head)))
		return (NULL);
	command_list = NULL;
	while (head)
	{
		command_list = ft_create_command(&head, command_list);
		if (!head)
			break ;
		head = head->next;
	}
	return (command_list);
}
