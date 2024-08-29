/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdhelper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:51 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/02 13:55:38 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern t_shell	g_shell;

char	*pwd_return_set_old(void)
{
	char	*path;

	path = ft_calloc(PATH_MAX, sizeof(char));
	getcwd(path, PATH_MAX);
	if (search_value_env_lst("OLDPWD") == NULL)
		add_env_lst(&g_shell.env_lst, "OLDPWD", path);
	if (search_value_env_lst("PWD") == NULL)
		add_env_lst(&g_shell.env_lst, "PWD", path);
	free(path);
	return (search_value_env_lst("PWD"));
}

int	oldpwd_not_set_check(void)
{
	if (search_value_env_lst("OLDPWD") != NULL)
		return (chdir(search_value_env_lst("OLDPWD")));
	else
		add_env_lst(&g_shell.env_lst, "OLDPWD", getcwd(NULL, 0));
	return (chdir(search_value_env_lst("OLDPWD")));
}

int	home_not_set_check(void)
{
	if (search_value_env_lst("HOME") == NULL)
	{
		g_shell.exit_status = ft_fprintf(2, "Error: HOME not set\n");
		return (-1);
	}
	return (chdir(search_value_env_lst("HOME")));
}
