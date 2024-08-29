/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokenizer_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:10:21 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:46:23 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*ft_lastnode(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_node	*ft_prev_node(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_add_back(t_node **list, t_node *new)
{
	if (!list)
		return ;
	if (!*list)
	{
		*list = new;
		new->prev = NULL;
	}
	else
	{
		(ft_lastnode(*list))->next = new;
		new->prev = ft_prev_node(*list);
	}
}

t_node	*ft_stack_new(char *str, int return_value)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = str;
	new->type = return_value;
	new->next = NULL;
	return (new);
}

int	ft_word_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] <= 12 && s[i] >= 9) || s[i] == 32 || s[i] == '<'
			|| s[i] == '>' || s[i] == '|')
			return (i);
		i++;
	}
	return (i);
}
