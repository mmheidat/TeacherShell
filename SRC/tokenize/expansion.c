/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:16:22 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 18:58:04 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*ft_strjoinchar(char *str, char c)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
	{
		free(str);
		return (NULL);
	}
	ft_strcpy(result, str);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*get_env_value(t_env *env, char *variable)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(variable, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*exp_utils(char *str, int *j, t_data *data)
{
	int		k;
	char	*variable;
	char	*result;

	k = *j + 1;
	while (str[k] && str[k] != ' ' && str[k] != '$'
		&& str[k] != '\'' && str[k] != '\"')
		k++;
	variable = ft_substr(str, *j + 1, k - *j - 1);
	if (!variable)
		return (NULL);
	result = get_env_value(data->envp_list, variable);
	free(variable);
	*j = k;
	return (result);
}

char	*expansion(char *str, int *j, t_data *data, t_quotes *inside_quotes)
{
	char	*result;

	if (str[*j + 1] == '?' && !inside_quotes->single_quote)
	{
		*j += 2;
		return (ft_itoa(data->exit_status));
	}
	if (inside_quotes->single_quote || str[*j + 1] == ' '
		|| str[*j + 1] == '\0' || str[*j + 1] == '$'
		|| str[*j + 1] == '\"' || str[*j + 1] == '\'')
	{
		(*j)++;
		return (ft_strdup("$"));
	}
	result = exp_utils(str, j, data);
	if (result)
		return (result);
	else
		return (ft_strdup(""));
}

void	expand_file_name(char *str, t_data *data, char **result)
{
	int			i;
	char		*expanded;
	char		*temp;
	t_quotes	inside_quotes;

	i = 0;
	initialize_quote(&inside_quotes);
	while (str[i])
	{
		update_quotes(&inside_quotes, str[i]);
		if (str[i] == '$' && inside_quotes.single_quote == 0)
		{
			expanded = expansion(str, &i, data, &inside_quotes);
			temp = ft_strjoin(*result, expanded);
			free(expanded);
		}
		else
			temp = ft_strjoinchar(*result, str[i++]);
		free(*result);
		*result = temp;
	}
}
