/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokenizer_token_type.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:59:35 by brahimb           #+#    #+#             */
/*   Updated: 2024/08/05 17:45:36 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_init_fill(t_fill *fill)
{
	fill->i = 0;
	fill->return_value = 0;
	fill->len = 0;
}

int	ft_sim_double_quote(char *s, char doubles)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == doubles)
			return (1);
		i++;
	}
	return (0);
}

int	ft_sim_single_quote(char *s, char single)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == single)
			return (1);
		i++;
	}
	return (0);
}

t_type	get_quote_type_token(char *rl)
{
	if (*rl == '\'')
	{
		if (!ft_sim_single_quote(rl + 1, 39))
			return (INVALID);
		return (SINGLE_QUOTE);
	}
	if (*rl == '\"')
	{
		if (!ft_sim_double_quote(rl + 1, 34))
			return (INVALID);
		return (DOUBLE_QUOTE);
	}
	return (WORD);
}

t_type	get_type_token(char *rl)
{
	if (*rl == '>')
	{
		if (*(rl + 1) == '>')
			return (REDIRECT_APPEND);
		return (REDIRECT_OUT);
	}
	if (*rl == '<')
	{
		if (*(rl + 1) == '<')
			return (REDIRECT_HEREDOC);
		return (REDIRECT_IN);
	}
	if (*rl == '|')
		return (PIPE);
	return (get_quote_type_token(rl));
}
/*t_type	get_type_token(char *rl)
{
	if (*rl == '>')
	{
		if (*(rl + 1) == '>')
			return (REDIRECT_APPEND);
		return (REDIRECT_OUT);
	}
	else if (*rl == '<')
	{
		if (*(rl + 1) == '<')
			return (REDIRECT_HEREDOC);
		return (REDIRECT_IN);
	}
	else if (*rl == '|')
		return (PIPE);
	else if (*rl == '\'')
	{
		if (!ft_sim_single_quote(rl + 1, 39))
			return (INVALID);
		return (SINGLE_QUOTE);
	}
	else if (*rl == '\"')
	{
		if (!ft_sim_double_quote(rl + 1, 34))
			return (INVALID);
		return (DOUBLE_QUOTE);
	}
	else
		return (WORD);
}*/