/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Find_childs_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:05:04 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/09 11:38:47 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

void	ft_search_in_set_path(t_exec *exec)
{
	char	*temp;
	char	*temp_one;
	char	*temp_search;
	char	*str;

	temp_search = ft_strdup(search_value_env_lst("PATH"));
	str = ft_strtok(temp_search, ":");
	while (str)
	{
		temp = ft_strjoin(str, "/");
		temp_one = ft_strjoin(temp, exec->tab[0]);
		exec->has_access = access(temp_one, X_OK);
		if (exec->has_access == 0)
		{
			exec->executable = temp_one;
			free(temp);
			break ;
		}
		str = ft_strtok(NULL, ":");
		free(temp);
		free(temp_one);
	}
	free(temp_search);
}

void	ft_search_in_bin_path(t_exec *exec)
{
	exec->has_access = access(exec->tab[0], X_OK);
	if (exec->has_access == 0)
	{
		exec->executable = exec->tab[0];
		exec->tab[0] = ft_get_cmd(exec->tab[0]);
	}
}

void	ft_unfound_in_bin_and_unset_path(void)
{
	char	*str;

	str = "minishell: No such file or directory\n";
	write(1, str, ft_strlen(str));
	g_shell.exit_status = -1;
	main_exit();
}

void	ft_unfound_in_bin_and_set_path(char *str)
{
	write(1, "find-the-command: command not found locally, ", 46);
	write(1, "searching in repositories ", 26);
	write(1, str, ft_strlen(str));
	write(1, "... \n", 5);
	g_shell.exit_status = -1;
	exit(g_shell.exit_status);
}

void	ft_execute(t_cmd *cmd, t_exec *exec)
{
	int	path_unset;

	path_unset = 0;
	exec->executable = NULL;
	exec->has_access = -1;
	if (search_value_env_lst("PATH"))
		ft_search_in_set_path(exec);
	else
		path_unset = 1;
	if (exec->has_access == -1)
		ft_search_in_bin_path(exec);
	if (exec->has_access == -1 && path_unset == 1)
		ft_unfound_in_bin_and_unset_path();
	if (exec->has_access == -1 && *exec->tab[0] != '\0'
		&& ft_strcmp(exec->tab[0], "export") != 0 && ft_strcmp(exec->tab[0],
			"unset") != 0 && ft_strncmp(exec->tab[0], "cd", 3) != 0)
		ft_unfound_in_bin_and_set_path(exec->tab[0]);
	ft_execute_path(cmd, exec);
}
