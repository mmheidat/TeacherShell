/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:46:58 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/10 20:00:21 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"


void free_data(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->envp)
		free_double_pointer(data->envp);
	if (data->path)
		free_double_pointer(data->path);
	if (data->tokens)
		free_double_pointer(data->tokens);
	if (data->envp_list)
		free_env(&data->envp_list);
	if (data->export_list)
		free_env(&data->export_list);
	if (data->files)
		free_files(data->files);
	if (data->cmd)
		free_cmd_memory(&data->cmd);
	close_fds();
}

void free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = temp;
	}
	*env = NULL;
}

void free_double_pointer(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	free_files(t_files *files)
{
	t_files	*temp;

	while (files)
	{
		temp = files->next;
		if (files->file_name)
			free(files->file_name);
		free(files);
		files = temp;
	}
}