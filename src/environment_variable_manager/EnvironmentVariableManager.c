/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnvironmentVariableManager.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:46:53 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 17:40:48 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	duplicate_env_lst(t_env **src, t_env **dest)
{
	t_env	*temp;

	temp = *src;
	*dest = NULL;
	while (temp)
	{
		add_env_lst(dest, temp->key, temp->value);
		temp = temp->next;
	}
}

void	print_env_lst_helper(t_env **env_lst, int mode, int fd)
{
	t_env	*temp;

	temp = *env_lst;
	while (temp)
	{
		if (mode == 1 && ft_strncmp(temp->value, "", 2) != 0
			&& ft_strncmp(temp->value, "\t", 2) != 0)
			ft_fprintf(fd, "declare -x %s=\"%s\"\n", temp->key, temp->value);
		if (mode == 1 && ft_strncmp(temp->value, "", 2) == 0)
			ft_fprintf(fd, "declare -x %s\n", temp->key);
		if (mode == 1 && ft_strncmp(temp->value, "\t", 2) == 0)
			ft_fprintf(fd, "declare -x %s=''\n", temp->key);
		if (mode == 2 && ft_strncmp(temp->value, "", 2) != 0)
			ft_fprintf(fd, "%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

void	print_env_lst(int fd, int mode)
{
	t_env	*env_lst;
	t_env	*temp;

	env_lst = g_shell.env_lst;
	temp = NULL;
	while (env_lst->prev)
		env_lst = env_lst->prev;
	if (mode == 1)
	{
		duplicate_env_lst(&g_shell.env_lst, &temp);
		sort_env_lst(&temp);
		print_env_lst_helper(&temp, mode, fd);
		free_env_lst(temp);
	}
	else
		print_env_lst_helper(&env_lst, mode, fd);
}

char	*search_value_env_lst(char *key)
{
	t_env	*env_lst;

	env_lst = g_shell.env_lst;
	while (env_lst->prev)
		env_lst = env_lst->prev;
	while (env_lst)
	{
		if (*env_lst->key && !ft_strcmp(env_lst->key, key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

int	initiliaze_envp(char **envp)
{
	t_env	*env_lst;

	env_lst = NULL;
	if (*envp == NULL)
	{
		add_env_lst(&env_lst, "SHLVL", "1");
		add_env_lst(&env_lst, "PWD", getcwd(NULL, 0));
		add_env_lst(&env_lst, "OLDPWD", "");
		add_env_lst(&env_lst, "HOME", "");
		add_env_lst(&env_lst, "PATH", "/usr/bin:/bin:/usr/sbin:/sbin");
		add_env_lst(&env_lst, "_", "./minishell");
		g_shell.env_lst = env_lst;
		return (0);
	}
	while (*envp)
	{
		if (add_env_lst(&env_lst, ft_strtok(*envp, "="), ft_strtok(NULL, "")))
			return (1);
		envp++;
	}
	while (env_lst->prev)
		env_lst = env_lst->prev;
	g_shell.env_lst = env_lst;
	return (0);
}
