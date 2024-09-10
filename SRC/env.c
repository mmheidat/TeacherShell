/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:09:03 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/10 18:43:54 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_key(t_env *current, char *key, char *value)
{
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value)
				free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	remove_env(t_env **env_list, t_cmd *token)
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	if (!token->content[1])
		return ;
	while (current)
	{
		if (ft_strcmp(current->key, token->content[1]) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			current->key = NULL;
			free(current->value);
			current->value = NULL;
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	add_env(t_env **env_list, char *key, char *value)
{
	t_env	*new_env;
	t_env	*current;

	current = *env_list;
	// if (check_key(current, key, value))
	// 	return ;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	if (*env_list == NULL)
		*env_list = new_env;
	else
	{
		current = *env_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_env;
	}
}

void	init_env(t_data *data, char **envp)
{
	int			i;
	char		*envp_key;
	char		*delimiter;
	i = 0;
	while (envp && envp[i])
	{
		envp_key = ft_strdup(envp[i]);
		delimiter = ft_strchr(envp_key, '=');
		if (delimiter)
		{
			*delimiter = '\0';
			add_env(&data->envp_list, envp_key, delimiter + 1);
			add_env(&data->export_list, envp_key, delimiter + 1);
		}
		free(envp_key);
		i++;
	}
}

void	add_temp_env(t_data *data, t_cmd *token)
{
	char	*delimiter;

	if (!token->content[1])
	{
		print_env(data->envp_list);
		return ;
	}
	delimiter = ft_strchr(token->content[1], '=');
	if (!delimiter)
	{
		printf("bash: env: %s: No such file or directory\n", token->content[1]);
		return ;
	}
	*delimiter = '\0';
	add_env(&data->envp_list, token->content[1], delimiter + 1);
	print_env(data->envp_list);
	return ;
}
