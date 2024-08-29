/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpanderHelper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:25:44 by brahimb           #+#    #+#             */
/*   Updated: 2024/07/29 20:43:58 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern t_shell	g_shell;

bool	is_escaped(const char *str, int pos)
{
	int	count;

	count = 0;
	while (pos > 0 && str[--pos] == '\\')
	{
		count++;
	}
	return (count % 2 != 0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}

char	*handle_double_dollar(char *result)
{
	char	*env_value;
	char	*new_result;

	env_value = search_value_env_lst("$");
	if (env_value != NULL)
		new_result = ft_strjoin(result, env_value);
	else
		new_result = ft_strjoin(result, "");
	return (new_result);
}

char	*handle_exit_status(char *result)
{
	char	*exit_status;
	char	*new_result;

	exit_status = ft_itoa(g_shell.exit_status);
	new_result = ft_strjoin(result, exit_status);
	free(exit_status);
	return (new_result);
}

char	*handle_variable(char *result, const char *value, int *i)
{
	int		j;
	char	*var_name;
	char	*env_value;
	char	*new_result;

	j = *i + 1;
	while (value[j] != '\0' && (ft_isalnum(value[j]) || value[j] == '_'))
		j++;
	var_name = ft_calloc(j - *i, sizeof(char));
	if (var_name == NULL)
		return (result);
	ft_strncpy(var_name, value + *i + 1, j - *i - 1);
	env_value = search_value_env_lst(var_name);
	free(var_name);
	if (env_value != NULL)
		new_result = ft_strjoin(result, env_value);
	else
		new_result = ft_strjoin(result, "");
	*i = j;
	return (new_result);
}
