/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:11:02 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/10 18:28:31 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	sort_export(t_env *env_list)
{
	int			size;
	t_env		**export_array;

	export_array = list_array(env_list, &size);
	if (export_array)
	{
		sort_array(export_array, size);
		free(export_array);
	}
	else
		printf("Error\n");
}

void	print_export(t_env *export_list)
{
	t_env	*current;

	current = export_list;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

void	handle_invalid_identifier(char *key, t_data *data)
{
	printf("bash: export: `%s': not a valid identifier\n", key);
	data->exit_status = 1;
	free(key);
}

void	process_key_value(char *token, t_data *data)
{
	char	*delimiter;
	char	*key;
	char	*value;

	delimiter = ft_strchr(token, '=');
	if (delimiter)
	{
		*delimiter = '\0';
		key = ft_strdup(token);
		if ((!ft_isalpha(key[0]) && key[0] != '_'))
			return (handle_invalid_identifier(key, data));
		value = ft_strdup(delimiter + 1);
		add_env(&(data->export_list), key, value);
		add_env(&(data->envp_list), key, value);
		free(key);
		// free(value);
	}
	else
	{
		key = ft_strdup(token);
		if (!ft_isalpha(key[0]) && key[0] != '_')
			return (handle_invalid_identifier(key, data));
		free(key);
	}
}

void	export(t_data *data, t_cmd *token)
{
	int	i;

	i = 1;
	if (!token->content[1])
	{
		data->exit_status = 0;
		return (sort_and_print_export(data->export_list));
	}
	while (token->content[i])
		process_key_value(token->content[i++], data);
	data->exit_status = 0;
}
