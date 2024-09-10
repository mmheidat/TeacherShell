/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_without_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 02:34:09 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 16:05:05 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

size_t	ft_countword(char const *s, char c)
{
	size_t			count;
	size_t			i;
	t_quotes		inside_quotes;

	initialize_quote(&inside_quotes);
	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && inside_quotes.single_quote == 0
			&& inside_quotes.double_quote == 0)
			count++;
		while (s[i] != c && s[i])
		{
			update_quotes(&inside_quotes, s[i]);
			i++;
		}
	}
	return (count);
}

char	*ft_strtrim_quotes(char *str, char quote1, char quote2)
{
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len == 0)
		return (str);
	while (str[start] == quote1 || str[start] == quote2)
		start++;
	end = len - 1;
	while (end > start && (str[end] == quote1 || str[end] == quote2))
		end--;
	return (ft_substr(str, start, end - start + 1));
}

void	free_split_memory(char **split, size_t i)
{
	if (!split)
		return ;
	while (i > 0)
		free(split[--i]);
	free(split);
}
