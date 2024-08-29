/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:12:32 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 15:56:29 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	g_shell;

int	main_exit(void)
{
	free(g_shell.pwd);
	free_env_lst(g_shell.env_lst);
	exit(g_shell.exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	path[PATH_MAX];

	if (argc != 1 || argv[1])
		printf("Error: too many arguments\n");
	else
	{
		initiliaze_signal();
		if (initiliaze_envp(envp))
			return (1);
		delete_env_lst(&g_shell.env_lst, "OLDPWD");
		getcwd(path, PATH_MAX);
		if (search_value_env_lst("PWD") == NULL)
			add_env_lst(&g_shell.env_lst, "PWD", getcwd(path, 0));
		g_shell.pwd = ft_strdup(search_value_env_lst("PWD"));
		if (search_value_env_lst("SHLVL") == NULL)
			add_env_lst(&g_shell.env_lst, "SHLVL", "1");
		g_shell.shlvl = ft_atoi(search_value_env_lst("SHLVL"));
		g_shell.shlvl_allowed = -1;
		g_shell.exit_status = cli();
		main_exit();
	}
	return (g_shell.exit_status);
}
