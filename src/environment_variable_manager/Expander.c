/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:55:15 by brahimb           #+#    #+#             */
/*   Updated: 2024/07/29 20:43:07 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <ctype.h>

extern t_shell	g_shell;

char	*expand_special_characters(char *result, const char *value, int *i)
{
	char	*new_result;

	if (value[*i + 1] == '$')
	{
		new_result = handle_double_dollar(result);
		*i += 2;
	}
	else if (value[*i + 1] == '?')
	{
		new_result = handle_exit_status(result);
		*i += 2;
	}
	else if (isalnum(value[*i + 1]) || value[*i + 1] == '_')
		new_result = handle_variable(result, value, i);
	else
	{
		new_result = ft_strjoin(result, "$");
		(*i)++;
	}
	return (new_result);
}

char	*copy_non_special_characters(char *result, const char *value, int *i)
{
	char	temp[2];
	char	*new_result;

	temp[0] = value[*i];
	temp[1] = '\0';
	new_result = ft_strjoin(result, temp);
	(*i)++;
	return (new_result);
}

char	*process_value(char *value)
{
	char	*result;
	char	*new_result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '$' && !is_escaped(value, i))
			new_result = expand_special_characters(result, value, &i);
		else
			new_result = copy_non_special_characters(result, value, &i);
		free(result);
		result = new_result;
	}
	return (result);
}

void	expand_env(t_node **node)
{
	t_node	*tmp;
	char	*value;
	char	*result;

	tmp = *node;
	value = tmp->value;
	if (ft_strchr(value, '$') == NULL)
		return ;
	result = process_value(value);
	free(tmp->value);
	tmp->value = result;
}

void	expander(t_node **node_list)
{
	t_node	*tmp;

	tmp = *node_list;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == DOUBLE_QUOTE)
			expand_env(&tmp);
		tmp = tmp->next;
	}
}
