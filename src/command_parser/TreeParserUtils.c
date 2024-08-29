/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeParserUtils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:46:23 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 13:49:54 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect_out	*ft_new_out(t_node *node)
{
	t_redirect_out	*new;

	new = malloc(sizeof(t_redirect_out));
	if (!new)
		return (NULL);
	new->name = node->next->value;
	new->type = node->type;
	new->fd = 0;
	new->next = NULL;
	return (new);
}

t_redirect_out	*ft_lastout(t_redirect_out *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	ft_add_out(t_cmd *list, t_redirect_out *new)
{
	if (!(list->list_out))
		list->list_out = new;
	else
		(ft_lastout(list->list_out))->next = new;
}

t_redirect_in	*ft_new_in(t_node *node)
{
	t_redirect_in	*new;

	new = malloc(sizeof(t_redirect_in));
	if (!new)
		return (NULL);
	new->name = node->next->value;
	new->type = node->type;
	new->fd = 0;
	new->next = NULL;
	return (new);
}

t_redirect_in	*ft_lastin(t_redirect_in *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
