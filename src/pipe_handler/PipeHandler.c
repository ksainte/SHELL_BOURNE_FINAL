/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PipeHandler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:24:28 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 11:24:39 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_handle_pipes(t_redirect_in *cmd_in, t_exec *exec)
{
	if (exec->i == 0)
		close(exec->out_pipe[0]);
	else if (exec->i == exec->cmd_size - 1)
	{
		close(exec->in_pipe[1]);
		if (!cmd_in)
			dup2(exec->in_pipe[0], 0);
		close(exec->in_pipe[0]);
	}
	else
	{
		close(exec->out_pipe[0]);
		close(exec->in_pipe[1]);
		if (!cmd_in)
			dup2(exec->in_pipe[0], 0);
		close(exec->in_pipe[0]);
	}
}
