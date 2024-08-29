/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnvironmentVariableManagerSpecial.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:23:44 by brahimb           #+#    #+#             */
/*   Updated: 2024/07/29 20:29:25 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*ptr;
	char		*token;
	int			count;

	if (str)
		ptr = str;
	if (!ptr || !*ptr)
		return (NULL);
	count = 0;
	while (ptr[count])
	{
		if (ft_strchr(delim, ptr[count]))
		{
			ptr[count] = '\0';
			token = ptr;
			ptr += count + 1;
			return (token);
		}
		count++;
	}
	token = ptr;
	ptr += count;
	return (token);
}

char	**env_lst_to_tab(t_env *env_lst)
{
	t_env	*tmp;
	char	**env_tab;
	int		i;

	tmp = env_lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
		return (NULL);
	i = 0;
	while (env_lst)
	{
		env_tab[i] = ft_strjoin(env_lst->key, "=");
		env_tab[i] = ft_strjoin(env_tab[i], env_lst->value);
		env_lst = env_lst->next;
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

void	sort_env_lst(t_env **env_lst)
{
	t_env	*temp;
	t_env	*temp2;
	char	*key;
	char	*value;

	temp = *env_lst;
	while (temp)
	{
		temp2 = temp->next;
		while (temp2)
		{
			if (ft_strncmp(temp->key, temp2->key, 2) > 0)
			{
				key = temp->key;
				value = temp->value;
				temp->key = temp2->key;
				temp->value = temp2->value;
				temp2->key = key;
				temp2->value = value;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}
