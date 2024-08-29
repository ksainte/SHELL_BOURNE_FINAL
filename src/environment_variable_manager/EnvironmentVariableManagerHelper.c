/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnvironmentVariableManagerHelper.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ks19 <ks19@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:08:49 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/04 18:53:55 by ks19             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env_lst(t_env *env_lst)
{
	t_env	*tmp;

	if (!env_lst)
		return ;
	while (env_lst->prev)
		env_lst = env_lst->prev;
	while (env_lst)
	{
		tmp = env_lst;
		env_lst = env_lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

int	edit_env_lst(t_env **env_lst, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_lst;
	if (!key || !value)
		return (1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	delete_env_lst(t_env **env_lst, char *key)
{
	t_env	*tmp;

	tmp = *env_lst;
	if (!key)
		return (1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			else
				*env_lst = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	add_env_lst(t_env **env_lst, char *key, char *value)
{
	t_env	*new_lst;
	t_env	*last_lst;

	new_lst = (t_env *)malloc(sizeof(t_env));
	if (!new_lst)
		return (1);
	if (!key || !value)
		return (0);
	last_lst = *env_lst;
	new_lst->key = ft_strdup(key);
	new_lst->value = ft_strdup(value);
	new_lst->next = NULL;
	if (*env_lst == NULL)
	{
		new_lst->prev = NULL;
		*env_lst = new_lst;
	}
	else
	{
		while (last_lst->next)
			last_lst = last_lst->next;
		last_lst->next = new_lst;
		new_lst->prev = last_lst;
	}
	return (0);
}
