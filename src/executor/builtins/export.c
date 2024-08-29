/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:45:59 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/06 16:12:21 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern t_shell	g_shell;

void	add_empty_key(t_env **env_lst, char *key, char *value)
{
	if (!search_value_env_lst(key))
		add_env_lst(env_lst, key, value);
}

void	export_key_value(char **strs)
{
	char	*key;
	char	*value;

	if (ft_strchr(*strs, '='))
	{
		key = ft_strtok(*strs, "=");
		value = ft_strtok(NULL, "=");
		if (!value)
			value = "\t";
		if (ft_strchr(key, '+'))
		{
			key = ft_strtok(key, "+");
			if (search_value_env_lst(key))
				edit_env_lst(&g_shell.env_lst, key,
					ft_strjoin(search_value_env_lst(key), value));
			else
				add_env_lst(&g_shell.env_lst, key, value);
		}
		else if (search_value_env_lst(key))
			edit_env_lst(&g_shell.env_lst, key, value);
		else
			add_env_lst(&g_shell.env_lst, key, value);
	}
	else
		add_empty_key(&g_shell.env_lst, *strs, "");
}

void	builtin_export(int fd, char **strs)
{
	char	**temp;

	temp = strs;
	g_shell.exit_status = 0;
	if (!strs[0])
		return (print_env_lst(fd, 1));
	while (*temp)
	{
		if (ft_isdigit(**temp) != 0 || **temp == '=')
		{
			ft_fprintf(fd, ">$ export: `%s': not a valid identifier\n", *temp);
			return ;
		}
		temp++;
	}
	while (*strs)
		export_key_value(strs++);
}
