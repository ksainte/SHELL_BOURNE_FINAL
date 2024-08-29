/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedirectionHandler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:28:56 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/09 11:33:00 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

int	handle_open_input(t_redirect_in *cmd_in, int in_child)
{
	int	in;

	in = open(cmd_in->name, O_RDONLY);
	if (in == -1)
	{
		write(1, "Error: No such file or directory \n", 34);
		g_shell.exit_status = -1;
		if (in_child == 1)
			main_exit();
	}
	return (in);
}

int	handle_heredoc(t_redirect_in *cmd_in, int in_child)
{
	int	pid;
	int	in;

	in = -1;
	if (in_child == 0)
	{
		pid = fork();
		if (pid == 0)
			in = ft_heredoc(cmd_in);
		while (wait(NULL) != -1)
			continue ;
	}
	else
		in = ft_heredoc(cmd_in);
	return (in);
}

int	ft_redirect_in(t_cmd *cmd, int in_child)
{
	int				in;
	t_redirect_in	*cmd_in;

	cmd_in = cmd->list_in;
	in = 0;
	if (cmd_in->next)
		cmd_in = ft_open_list_in(cmd_in, in_child);
	if (!cmd_in || g_shell.sig_c == 1)
		return (-1);
	if (cmd_in->type == 4)
		in = handle_open_input(cmd_in, in_child);
	else if (cmd_in->type == 6)
		in = handle_heredoc(cmd_in, in_child);
	if (in_child == 0 && in != -1)
		close(in);
	return (in);
}

t_redirect_out	*ft_open_list_out(t_redirect_out *cmd_out)
{
	int	out;

	while (cmd_out->next)
	{
		if (cmd_out->type == 7)
			out = open(cmd_out->name, O_CREAT, 0644);
		else if (cmd_out->type == 5)
			out = open(cmd_out->name, O_TRUNC | O_CREAT, 0644);
		cmd_out = cmd_out->next;
		close(out);
	}
	return (cmd_out);
}

int	ft_redirect_out(t_cmd *cmd)
{
	int				out;
	t_redirect_out	*cmd_out;

	cmd_out = cmd->list_out;
	out = 0;
	if (cmd_out->next)
		cmd_out = ft_open_list_out(cmd_out);
	if (cmd_out->type == 5)
		out = open(cmd_out->name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		out = open(cmd_out->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (out);
}
/*t_redirect_in	*ft_open_list_in(t_redirect_in *cmd_in, int in_child)
{
	int	in;

	while (cmd_in->next)
	{
		if (cmd_in->type == 4)
		{
			in = open(cmd_in->name, O_RDONLY);
			if (in == -1)
			{
				if (in_child == 1)
				{
					ft_error();
					g_shell.exit_status = -1;
					exit(g_shell.exit_status);
				}
				else
				{
					ft_error();
					return (NULL);
				}
			}
		}
		else if (cmd_in->type == 6)
		{
			in = ft_heredoc(cmd_in);
		}
		cmd_in = cmd_in->next;
		close(in);
	}
	return (cmd_in);
}

int	ft_redirect_in(t_cmd *cmd, int in_child)
{
	int				in;
	t_redirect_in	*cmd_in;
	int				pid;

	cmd_in = cmd->list_in;
	in = 0;
	if (cmd_in->next)
		cmd_in = ft_open_list_in(cmd_in, in_child);
	if (!cmd_in)
		return (-1);
	if (cmd_in->type == 4)
	{
		in = open(cmd_in->name, O_RDONLY);
		if (in == -1)
		{
			if (in_child == 1)
			{
				ft_error();
				g_shell.exit_status = -1;
				exit(g_shell.exit_status);
			}
			else
			{
				ft_error();
				return (-1);
			}
		}
	}
	else if (cmd_in->type == 6)
	{
		if (in_child == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				in = ft_heredoc(cmd_in);
			}
			while (wait(NULL) != -1)
			{
			}
			return (0);
		}
		else
			in = ft_heredoc(cmd_in);
	}
	if (in_child == 0)
		close(in);
	return (in);
}*/