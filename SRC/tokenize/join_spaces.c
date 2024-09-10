/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 23:33:35 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 16:21:14 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	count_redirect(char *line)
{
	int			i;
	int			count;
	t_quotes	inside_quotes;

	initialize_quote(&inside_quotes);
	i = 0;
	count = ft_strlen(line);
	while (line[i])
	{
		update_quotes(&inside_quotes, line[i]);
		if (((line[i] == '>' || line[i] == '<')) && inside_quotes.single_quote
			== 0 && inside_quotes.double_quote == 0)
		{
			count = count + 2;
			if (line[i + 1] == '>' || line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (count);
}

void	append_redirection(char *line, char **new_line, int *i, int *x)
{
	(*new_line)[(*x)++] = ' ';
	(*new_line)[(*x)++] = line[(*i)++];
	if (line[*i] == '>' || line[*i] == '<')
		(*new_line)[(*x)++] = line[(*i)++];
	(*new_line)[(*x)++] = ' ';
}

char	*join_spaces(char *line)
{
	char		*new_line;
	int			i;
	int			x;
	t_quotes	inside_quotes;

	i = 0;
	x = 0;
	new_line = malloc(count_redirect(line) + 1);
	if (!new_line)
		return (NULL);
	initialize_quote(&inside_quotes);
	while (line[i])
	{
		update_quotes(&inside_quotes, line[i]);
		if ((line[i] == '>' || line[i] == '<')
			&& inside_quotes.single_quote == 0
			&& inside_quotes.double_quote == 0)
			append_redirection(line, &new_line, &i, &x);
		else
			new_line[x++] = line[i++];
	}
	new_line[x] = '\0';
	free(line);
	return (new_line);
}
