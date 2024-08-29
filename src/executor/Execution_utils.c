/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:08:18 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:41:00 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

char	*ft_get_cmd(char *str)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(str, 47);
	while (tab[i])
		i++;
	return (tab[i - 1]);
}

void	ft_error(void)
{
	write(2, "Error\n", 6);
}

int	is_builtin(char **tab)
{
	if (!(ft_strncmp(tab[0], "echo", 5)) || !(ft_strncmp(tab[0], "export", 7))
		|| !(ft_strncmp(tab[0], "pwd", 4)) || !(ft_strncmp(tab[0], "env", 4))
		|| !(ft_strncmp(tab[0], "unset", 6)) || !(ft_strncmp(tab[0], "cd", 3)))
		return (1);
	return (0);
}

void	ft_exit_child(void)
{
	g_shell.exit_status = -1;
	main_exit();
}

void	ft_error_arg(void)
{
	ft_error();
	ft_exit_child();
}
