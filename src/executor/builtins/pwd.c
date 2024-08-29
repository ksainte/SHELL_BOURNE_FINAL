/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:18:42 by brahimb           #+#    #+#             */
/*   Updated: 2024/07/29 20:42:01 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

extern t_shell	g_shell;

void	builtin_pwd(int fd)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_fprintf(fd, "%s\n", path);
	g_shell.exit_status = 0;
}
