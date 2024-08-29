/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brahimb <brahimb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:28:34 by ks19              #+#    #+#             */
/*   Updated: 2024/08/05 17:45:23 by brahimb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotes(char *rl, int *len)
{
	char	*str;

	str = NULL;
	*len = ft_handle_quotes(rl);
	if (*len == -1)
		return (NULL);
	str = ft_substr(rl, 0, *len);
	if (!str)
		return (NULL);
	ft_trim_spaces(str);
	return (str);
}

char	*handle_redirect(char *rl, int *len, int size)
{
	char	*str;

	str = ft_substr(rl, 0, size);
	if (!str)
		return (NULL);
	*len = size;
	return (str);
}

char	*ft_fill_token(char *rl, int value, int *len)
{
	if (value == SINGLE_QUOTE || value == DOUBLE_QUOTE)
		return (handle_quotes(rl, len));
	if (value == REDIRECT_IN || value == REDIRECT_OUT)
		return (handle_redirect(rl, len, 1));
	if (value == REDIRECT_APPEND || value == REDIRECT_HEREDOC)
		return (handle_redirect(rl, len, 2));
	if (value == PIPE)
		return (handle_redirect(rl, len, 1));
	return (handle_quotes(rl, len));
}

char	*ft_filled_token(char *rl, int i, int *len, int *return_value)
{
	char	*tmp;

	*return_value = get_type_token(rl + i);
	if (*return_value == INVALID)
		return (NULL);
	tmp = ft_fill_token(rl + i, *return_value, len);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

t_node	*ft_tokenize(char *rl)
{
	t_node	*node;
	t_fill	fill;
	char	*tmp;

	ft_init_fill(&fill);
	node = NULL;
	while (rl[fill.i])
	{
		if ((rl[fill.i] <= 12 && rl[fill.i] >= 9) || rl[fill.i] == 32)
			fill.i++;
		else
		{
			tmp = ft_filled_token(rl, fill.i, &fill.len, &fill.return_value);
			if (tmp == NULL)
			{
				ft_free_nodes(&node);
				return (NULL);
			}
			ft_add_back(&node, ft_stack_new(tmp, fill.return_value));
		}
		fill.i = fill.i + fill.len;
		fill.len = 0;
	}
	return (node);
}
// t_node	*ft_tokenize(char *rl)
// {
// 	t_node	*node;
// 	int		i;
// 	int		return_value;
// 	char	*tmp;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	node = NULL;
// 	while (rl[i])
// 	{
// 		if ((rl[i] <= 12 && rl[i] >= 9) || rl[i] == 32)
// 			i++;
// 		else if (rl[i])
// 		{
// 			return_value = get_type_token(rl + i);
// 			if (return_value == INVALID)
// 			{
// 				ft_free_nodes(&node);
// 				return (NULL);
// 			}
// 			tmp = ft_fill_token(rl + i, return_value, &len);
// 			if (tmp == NULL)
// 			{
// 				ft_free_nodes(&node);
// 				return (NULL);
// 			}
// 			ft_add_back(&node, ft_stack_new(tmp, return_value));
// 		}
// 		i = i + len;
// 		len = 0;
// 	}
// 	return (node);
// }
/*char	*ft_fill_token(char *rl, int value, int *len)
{
	char	*str;

	if (value == SINGLE_QUOTE || value == DOUBLE_QUOTE)
	{
		*len = ft_handle_quotes(rl);
		if (*len == -1)
			return (NULL);
		str = ft_substr(rl, 0, *len);
		if (!str)
			return (NULL);
		ft_trim_spaces(str);
	}
	else if (value == REDIRECT_IN || value == REDIRECT_OUT)
	{
		str = ft_substr(rl, 0, 1);
		if (!str)
			return (NULL);
		*len = 1;
	}
	else if (value == REDIRECT_APPEND || value == REDIRECT_HEREDOC)
	{
		str = ft_substr(rl, 0, 2);
		if (!str)
			return (NULL);
		*len = 2;
	}
	else if (value == PIPE)
	{
		str = ft_substr(rl, 0, 1);
		if (!str)
			return (NULL);
		*len = 1;
	}
	else
	{
		*len = ft_handle_quotes(rl);
		if (*len == -1)
			return (NULL);
		str = ft_substr(rl, 0, *len);
		if (!str)
			return (NULL);
		ft_trim_spaces(str);
	}
	return (str);
}*/