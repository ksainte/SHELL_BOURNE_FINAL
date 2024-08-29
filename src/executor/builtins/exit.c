/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:58:31 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 15:57:56 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern t_shell	g_shell;

int	ft_is_numeric(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	check_exit_code(int fd, char *str)
{
	int		i;
	char	*temp;
	char	*first_tok;

	i = 0;
	temp = ft_strtok(str, " ");
	temp = ft_strtok(NULL, " ");
	first_tok = temp;
	if (temp == NULL)
		return (0);
	while (temp != NULL)
	{
		if (i++ == 1)
		{
			ft_fprintf(fd, "exit: too many arguments\n");
			return (23);
		}
		if (!ft_is_numeric(temp))
		{
			ft_fprintf(fd, "exit: %s: numeric argument required\n", temp);
			return (EXIT_NUMERIC_ERROR);
		}
		temp = ft_strtok(NULL, " ");
	}
	return (ft_atoi(first_tok));
}

void	builtin_exit(int fd, char **strs)
{
	char	*int_str;
	char	*str_temp;

	g_shell.exit_status = 0;
	if (*strs == NULL)
		main_exit();
	str_temp = ft_strdup(*strs++);
	while (*strs != NULL)
	{
		int_str = ft_strjoin(str_temp, " ");
		free(str_temp);
		str_temp = ft_strjoin(int_str, *strs);
		free(int_str);
		strs++;
	}
	g_shell.exit_status = check_exit_code(fd, str_temp);
	free(str_temp);
	if (g_shell.exit_status == 23 || g_shell.exit_status == EXIT_NUMERIC_ERROR)
		return ;
	main_exit();
}
