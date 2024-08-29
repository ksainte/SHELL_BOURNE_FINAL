/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:47:49 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:09:02 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern t_shell	g_shell;

void	builtin_unset(char **strs)
{
	g_shell.exit_status = 0;
	while (*++strs)
	{
		if (ft_strcmp(*strs, "_") != 0)
		{
			delete_env_lst(&g_shell.env_lst, *strs);
		}
	}
}
