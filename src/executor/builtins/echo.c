/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:03:24 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/06 16:01:36 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_option(char *str)
{
	if (*str != '-' || *(str + 1) != 'n')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	builtin_echo(char **strs, int fd)
{
	bool	new_line;

	new_line = true;
	strs++;
	while (*strs != NULL && check_option(*strs))
	{
		new_line = false;
		strs++;
	}
	while (*strs)
	{
		if (**strs == '-' && !new_line && ft_strlen(*strs) != 1)
		{
			strs++;
			continue ;
		}
		write(fd, *strs, ft_strlen(*strs));
		strs++;
		if (*strs)
			write(fd, " ", 1);
	}
	if (new_line)
		write(fd, "\n", 1);
}
