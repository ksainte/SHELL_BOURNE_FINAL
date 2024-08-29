/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandlerHelper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:37:53 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:49:46 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	handle_open_error(int in_child)
{
	write(1, "Error: No such file or directory \n", 34);
	g_shell.exit_status = -1;
	if (in_child == 1)
		main_exit();
}

int	open_file(t_redirect_in *cmd_in, int in_child)
{
	int	in;

	in = open(cmd_in->name, O_RDONLY);
	if (in == -1)
		handle_open_error(in_child);
	return (in);
}

t_redirect_in	*ft_open_list_in(t_redirect_in *cmd_in, int in_child)
{
	int	in;

	while (cmd_in->next)
	{
		if (cmd_in->type == 4)
		{
			in = open_file(cmd_in, in_child);
			if (in == -1)
				return (NULL);
		}
		else if (cmd_in->type == 6)
		{
			in = handle_heredoc(cmd_in, in_child);
		}
		cmd_in = cmd_in->next;
		close(in);
	}
	return (cmd_in);
}
