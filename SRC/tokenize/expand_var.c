/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:38:08 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/10 20:03:52 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	expand_files(t_files *files, t_data *data)
{
	char		*result;
	t_files		*temp;

	temp = files;
	while (files)
	{
		result = ft_strdup("");
		expand_file_name(files->file_name, data, &result);
		free(files->file_name);
		files->file_name = result;
		files = files->next;
	}
	files = temp;
}

void	expand_variable_content(char *str, t_data *data, char **result)
{
	int			i;
	char		*expanded;
	t_quotes	inside_quotes;
	char		*temp;

	i = 0;
	temp = NULL;
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
		{
			temp = ft_strjoinchar(*result, str[i++]);
			free(*result);
		}
		*result = ft_strdup(temp);
		free(temp);
	}
}

void	expand_cmd_content(t_cmd *cmd, t_data *data)
{
	int		j;
	char	*result;

	j = 0;
	while (cmd->content && cmd->content[j])
	{
		result = ft_strdup("");
		expand_variable_content(cmd->content[j], data, &result);
		if (!result)
			return ;
		free(cmd->content[j]);
		cmd->content[j] = ft_strdup(result);
		free(result);
		j++;
	}
}

void	expand_variables(t_cmd **cmd, t_data *data)
{
	t_cmd	*temp;

	if (!cmd || !*cmd)
		return ;
	temp = *cmd;
	while (*cmd)
	{
		expand_cmd_content(*cmd, data);
		expand_files((*cmd)->files, data);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}
