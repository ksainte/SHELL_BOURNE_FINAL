/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:11:26 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 16:30:12 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_free_table(char **table)
{
	int	i;

	i = 0;
	while (*(table + i) != NULL)
	{
		free(*(table + i));
		i++;
	}
	free(table);
}

void	print_cmd_args(t_args *cmd_args)
{
	while (cmd_args)
	{
		printf("cmd arg is:%s\n", cmd_args->arg_value);
		cmd_args = cmd_args->next;
	}
}

void	print_cmd_redirect_in(t_redirect_in *cmd_in)
{
	while (cmd_in)
	{
		printf("cmd redirect-in name is:%s\n", cmd_in->name);
		printf("cmd redirect-in type is:%d\n", cmd_in->type);
		cmd_in = cmd_in->next;
	}
}

void	print_cmd_redirect_out(t_redirect_out *cmd_out)
{
	while (cmd_out)
	{
		printf("cmd redirect-out name is:%s\n", cmd_out->name);
		printf("cmd redirect-out type is:%d\n", cmd_out->type);
		cmd_out = cmd_out->next;
	}
}

void	ft_print_commands(t_node *node_list, t_cmd *cmd)
{
	print_node_list(node_list);
	if (cmd)
		printf("First command is:\n");
	while (cmd)
	{
		printf("cmd name is:%s\n", cmd->name);
		print_cmd_args(cmd->args);
		print_cmd_redirect_in(cmd->list_in);
		print_cmd_redirect_out(cmd->list_out);
		cmd = cmd->next;
		if (cmd)
			printf("\nNew command:\n");
	}
}
/*void	ft_print_commands(t_node *node_list, t_cmd *cmd)
{
	t_args			*cmd_args;
	t_redirect_in	*cmd_in;
	t_redirect_out	*cmd_out;

	if (cmd)
	{
		cmd_args = cmd->args;
		cmd_in = cmd->list_in;
		cmd_out = cmd->list_out;
	}
	printf("original node list:\n");
	while (node_list)
	{
		printf("node has value:%s and type:%d\n", node_list->value,
			node_list->type);
		node_list = node_list->next;
	}
	if (cmd)
		printf("First command is:\n");
	while (cmd)
	{
		printf("cmd name is:%s\n", cmd->name);
		while (cmd_args)
		{
			printf("cmd arg is:%s\n", cmd_args->arg_value);
			cmd_args = cmd_args->next;
		}
		while (cmd_in)
		{
			printf("cmd redirect-in name is:%s\n", cmd_in->name);
			printf("cmd redirect-in type is:%d\n", cmd_in->type);
			cmd_in = cmd_in->next;
		}
		while (cmd_out)
		{
			printf("cmd redirect-out name is:%s\n", cmd_out->name);
			printf("cmd redirect-out type is:%d\n", cmd_out->type);
			cmd_out = cmd_out->next;
		}
		cmd = cmd->next;
		if (cmd)
		{
			cmd_args = cmd->args;
			cmd_in = cmd->list_in;
			cmd_out = cmd->list_out;
		}
		if (cmd)
			printf("\nNew command:\n");
	}
}
*/