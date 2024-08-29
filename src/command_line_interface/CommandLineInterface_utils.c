/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandLineInterface_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:15:28 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 17:00:24 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_calloc_cmd_len(t_cmd *cmd)
{
	int		i;
	t_args	*cmd_args;
	char	**tab;

	i = 0;
	cmd_args = cmd->args;
	if (cmd->name)
		i++;
	while (cmd_args)
	{
		i++;
		cmd_args = cmd_args->next;
	}
	tab = calloc(sizeof(char *), i + 1);
	return (tab);
}

char	**ft_fill_tab(char **tab, t_cmd *cmd)
{
	int		i;
	t_args	*cmd_args;

	cmd_args = cmd->args;
	if (cmd->name == NULL)
		*tab = "\0";
	else
		*tab = cmd->name;
	i = 1;
	while (cmd_args)
	{
		*(tab + i) = cmd_args->arg_value;
		cmd_args = cmd_args->next;
		i++;
	}
	*(tab + i) = NULL;
	return (tab);
}

int	ft_cmd_size(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	ft_heredoc_in_current_command(t_cmd *cmd)
{
	t_redirect_in	*cmd_in;

	cmd_in = cmd->list_in;
	if (cmd_in)
	{
		while (cmd_in)
		{
			if (cmd_in->type == 6)
				return (1);
			cmd_in = cmd_in->next;
		}
	}
	return (0);
}

int	check_only_space(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}
