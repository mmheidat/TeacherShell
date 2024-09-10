/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:40:32 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/10 18:02:27 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	skip_delimiters(char const **s, char c)
{
	while (**s == c && **s)
		(*s)++;
}

char	*get_word(const char **s, t_quotes *quotes, char c, size_t *len)
{
	const char	*start;

	start = *s;
	while (**s && (**s != c || quotes->single_quote || quotes->double_quote))
	{
		update_quotes(quotes, **s);
		(*s)++;
	}
	*len = *s - start;
	return (ft_substr(start, 0, *len));
}

void	process_word(t_process_data *data)
{
	size_t		word_len;
	char		*word;

	word = get_word(data->s, data->quotes, data->c, &word_len);
	data->split[*data->i] = ft_strdup(word);
	free(word);
	if (!data->split[*data->i])
	{
		free_split_memory(data->split, *data->i);
		exit(1);
	}
	(*data->i)++;
}

char	**ft_split_without_quotes(char const *s, char c)
{
	size_t			i;
	t_quotes		quotes;
	t_process_data	data;

	i = 0;
	if (!s)
		return (NULL);
	initialize_quote(&quotes);
	data.split = malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!data.split)
		return (NULL);
	data.s = &s;
	data.quotes = &quotes;
	data.i = &i;
	data.c = c;
	while (*s)
	{
		skip_delimiters(&s, c);
		if (*s)
			process_word(&data);
	}
	data.split[i] = NULL;
	return (data.split);
}

void	handle_error(t_data *data)
{
	write(2, "Syntax Error\n", 13);
	data->exit_status = 258;
}
