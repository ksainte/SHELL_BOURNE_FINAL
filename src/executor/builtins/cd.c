/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:25:30 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/02 13:55:35 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern t_shell	g_shell;

int	execute_cdhelper(char *s)
{
	char	*path;
	int		result;

	path = ft_calloc(PATH_MAX, sizeof(char));
	result = -1;
	if (ft_strcmp(s, "..") == 0)
	{
		ft_strlcpy(path, pwd_return_set_old(), PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, s, PATH_MAX);
		result = chdir(path);
		free(path);
		return (result);
	}
	if (s[0] != '/')
	{
		getcwd(path, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, s, PATH_MAX);
		result = chdir(path);
		free(path);
		return (result);
	}
	return (result);
}

int	execute_cd(char *s)
{
	if (s == NULL || *s == '\0' || ft_strcmp(s, "~") == 0)
		return (home_not_set_check());
	if (ft_strcmp(s, "-") == 0)
		return (oldpwd_not_set_check());
	if (ft_strcmp(s, ".") == 0)
		return (chdir(pwd_return_set_old()));
	if (execute_cdhelper(s) == 0)
		return (0);
	return (chdir(s));
}

void	builtin_cd(int fd, char *s)
{
	char	path[PATH_MAX];
	t_env	*env_lst;
	int		returnvalue;

	env_lst = g_shell.env_lst;
	returnvalue = execute_cd(s);
	if (returnvalue == -2)
	{
		g_shell.exit_status = ft_fprintf(fd, "Error: OLDPWD not set\n");
	}
	else if (returnvalue != -1)
	{
		getcwd(path, PATH_MAX);
		if (search_value_env_lst("PWD") == NULL)
			add_env_lst(&env_lst, "PWD", path);
		edit_env_lst(&env_lst, "OLDPWD", search_value_env_lst("PWD"));
		edit_env_lst(&env_lst, "PWD", path);
	}
	else
	{
		ft_fprintf(fd, "Error: cd\n");
		edit_env_lst(&env_lst, "PWD", path);
		chdir(g_shell.pwd);
	}
	g_shell.exit_status = returnvalue;
}
