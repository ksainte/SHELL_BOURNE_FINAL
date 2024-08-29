/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:26:38 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 11:27:28 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_newline_to_null(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

void	ft_null_to_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i + 1] != '\0')
		return ;
	str[i] = '\n';
}

int	ft_cmp_gnl_word(char *gnl, char *word)
{
	int	return_value;

	return_value = -1;
	ft_newline_to_null(gnl);
	return_value = ft_strncmp(gnl, word, ft_strlen(word) + 1);
	ft_null_to_newline(gnl);
	return (return_value);
}

int	ft_heredoc(t_redirect_in *cmd_in)
{
	int		pipes[2];
	char	*str;

	signal_to_default_behaviour();
	pipe(pipes);
	str = get_next_line(0);
	while (ft_cmp_gnl_word(str, cmd_in->name) != 0)
	{
		ft_putstr_fd(str, pipes[1]);
		str = get_next_line(0);
	}
	close(pipes[1]);
	initiliaze_signal();
	return (pipes[0]);
}
