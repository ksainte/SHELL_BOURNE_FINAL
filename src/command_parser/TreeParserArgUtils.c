/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeParserArgUtils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:46:19 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 13:47:16 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_args	*ft_new_arg(t_node *node)
{
	t_args	*new;

	new = malloc(sizeof(t_args));
	if (!new)
		return (NULL);
	new->arg_value = node->value;
	new->next = NULL;
	return (new);
}

t_args	*ft_lastarg(t_args *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_add_arg(t_cmd *list, t_args *new)
{
	if (!(list->args))
		list->args = new;
	else
		(ft_lastarg(list->args))->next = new;
}

void	ft_fill_word_or_quote(t_node *node, t_cmd *current_cmd)
{
	if (current_cmd->has_cmd == 0)
	{
		current_cmd->name = node->value;
		current_cmd->has_cmd = 1;
	}
	else
	{
		ft_add_arg(current_cmd, ft_new_arg(node));
	}
}
