/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLineInterface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:48 by ksainte           #+#    #+#             */
/*   Updated: 2024/08/05 17:41:47 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

int	read_input(char **rl)
{
	*rl = readline(">$ ");
	g_shell.sig_c = 0;
	if (*rl == NULL)
	{
		printf("exit\n");
		return (0);
	}
	return (1);
}

int	handle_input(char *rl, t_node **node_list, t_cmd **cmd_list)
{
	if (*rl == '\0' || check_only_space(rl) == 1)
	{
		free(rl);
		return (0);
	}
	add_history(rl);
	*node_list = ft_tokenize(rl);
	if (*node_list)
	{
		expander(node_list);
		*cmd_list = ft_parse(*node_list);
	}
	return (1);
}

void	execute_commands(t_node *node_list, t_cmd *cmd_list)
{
	if (cmd_list)
		ft_execve(cmd_list);
	if (!node_list)
		printf("Quote Syntax error\n");
	else if (!cmd_list)
		printf("Grammar Syntax error\n");
}

int	cli(void)
{
	char	*rl;
	t_node	*node_list;
	t_cmd	*cmd_list;

	node_list = NULL;
	cmd_list = NULL;
	while (1)
	{
		if (!read_input(&rl))
			break ;
		if (!handle_input(rl, &node_list, &cmd_list))
			continue ;
		execute_commands(node_list, cmd_list);
		free(rl);
		ft_free_nodes(&node_list);
		ft_free_cmds(&cmd_list);
	}
	return (0);
}
/*int	cli(void)
{
	char	*rl;
	t_node	*node_list;
	t_cmd	*cmd_list;

	node_list = NULL;
	cmd_list = NULL;
	while (1)
	{
		rl = readline(">$ ");
		g_shell.sig_c = 0;
		if (rl == NULL)
		{
			printf("exit\n");
			break ;
		}
		else if (*rl == '\0' || check_only_space(rl) == 1)
		{
			free(rl);
			continue ;
		}
		add_history(rl);
		node_list = ft_tokenize(rl);
		if (node_list)
		{
			expander(&node_list);
			cmd_list = ft_parse(node_list);
		}
		if (cmd_list)
			ft_execve(cmd_list);
		if (!node_list)
			printf("Quote Syntax error\n");
		else if (!cmd_list)
			printf("Grammar Syntax error\n");
		free(rl);
		ft_free_nodes(&node_list);
	}
	return (0);
}
*/