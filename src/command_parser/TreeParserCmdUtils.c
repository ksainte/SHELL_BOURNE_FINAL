/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeParserCmdUtils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:44:11 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 14:25:54 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_grammar_check(t_node *list)
{
	while (list)
	{
		if (list->type == 8)
		{
			if (!(list->next) || list->next->type == 8)
				return (0);
			if (!(list->prev))
				return (0);
		}
		if ((list->type >= 4 && list->type <= 7))
		{
			if ((!(list->next)) || (list->next->type != 1
					&& list->next->type != 2 && list->next->type != 3))
				return (0);
		}
		list = list->next;
	}
	return (1);
}

t_cmd	*ft_new_cmd(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->has_cmd = 0;
	new->name = NULL;
	new->args = NULL;
	new->next = NULL;
	new->list_in = NULL;
	new->list_out = NULL;
	return (new);
}

t_cmd	*ft_lastcmd(t_cmd *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_cmd	*ft_add_cmd(t_cmd *list, t_cmd *new)
{
	if (!list)
		list = new;
	else
		(ft_lastcmd(list))->next = new;
	return (list);
}
