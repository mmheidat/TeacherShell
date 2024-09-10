/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:16:44 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/05 22:48:09 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	initialize_quote(t_quotes *inside_quotes)
{
	inside_quotes->single_quote = 0;
	inside_quotes->double_quote = 0;
}

int	update_quotes(t_quotes *inside_quotes, char c)
{
	if (c == '\'' && inside_quotes->single_quote
		== 0 && inside_quotes->double_quote == 0)
		inside_quotes->single_quote = 1;
	else if (c == '\'' && inside_quotes->single_quote
		== 1 && inside_quotes->double_quote == 0)
		inside_quotes->single_quote = 0;
	else if (c == '\"' && inside_quotes->double_quote
		== 0 && inside_quotes->single_quote == 0)
		inside_quotes->double_quote = 1;
	else if (c == '\"' && inside_quotes->double_quote
		== 1 && inside_quotes->single_quote == 0)
		inside_quotes->double_quote = 0;
	return (1);
}

int	is_invalid_redirection(char c, char prev)
{
	return ((c == '\0') || (c == '>' || c == '<')
		|| (c == '|' || c == ';') || (prev == '>' && c == '>')
		|| (prev == '<' && c == '<'));
}

int	is_pipe_error(char c, int index, char next_char)
{
	return ((c == '|' && !next_char && index == 0) || next_char == '|');
}

void	free_tokens2(t_cmd **head)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		while (tmp->content[i])
			free(tmp->content[i++]);
		free(tmp->content);
		free(tmp);
	}
}
