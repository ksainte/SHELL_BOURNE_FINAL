/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing_utilshelper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:58:58 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 11:59:25 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_table(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

void	print_node_list(t_node *node_list)
{
	printf("original node list:\n");
	while (node_list)
	{
		printf("node has value:%s and type:%d\n", node_list->value,
			node_list->type);
		node_list = node_list->next;
	}
}
