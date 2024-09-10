/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:25:46 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/05 12:04:52 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_quotes(char *str)
{
	int			i;
	t_quotes	inside_quotes;

	i = 0;
	initialize_quote(&inside_quotes);
	while (str[i])
	{
		update_quotes(&inside_quotes, str[i]);
		i++;
	}
	if (inside_quotes.single_quote == 1 || inside_quotes.double_quote == 1)
		return (1);
	return (0);
}

int	check_redirection(char *str)
{
	int			i;
	t_quotes	inside_quotes;

	i = 0;
	initialize_quote(&inside_quotes);
	while (str[i])
	{
		update_quotes(&inside_quotes, str[i]);
		if ((str[i] == '>' || str[i] == '<') && inside_quotes.single_quote
			== 0 && inside_quotes.double_quote == 0)
		{
			if (validate_direction(str, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	validate_direction(char *str, int i)
{
	t_quotes	quotes;

	initialize_quote(&quotes);
	update_quotes(&quotes, str[i]);
	if (str[++i] == '\0')
	{
		printf("Error: redirection not valid\n");
		return (1);
	}
	if (is_invalid_redirection(str[i], str[i - 1]))
	{
		if ((str[i] == '>' || str[i] == '<') && str[i - 1] == str[i])
			i++;
		while (str[i] == ' ')
			i++;
		if (is_invalid_redirection(str[i], str[i - 1]))
		{
			printf("Error: redirection not valid\n");
			return (1);
		}
	}
	return (0);
}

int	check_pipes(char *str)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	initialize_quote(&quotes);
	while (*str == ' ')
		str++;
	while (str[i])
	{
		update_quotes(&quotes, str[i]);
		if (str[i] == '|' && !quotes.single_quote && !quotes.double_quote)
		{
			if (is_pipe_error(str[i + 1], i, str[i + 1]))
				return (1);
			while (str[++i] == ' ')
				;
			if (str[i] == '\0' || str[i] == '|')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	parsing(char *str)
{
	if (check_quotes(str) == 1)
		return (1);
	if (check_redirection(str) == 1)
		return (1);
	if (check_pipes(str) == 1)
		return (1);
	return (0);
}
