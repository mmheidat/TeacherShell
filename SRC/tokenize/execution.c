/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:59:03 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/07 05:31:29 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	**get_path(t_env *envp_list)
{
	char	*path;
	char	**path_split;
	t_env	*tmp;

	path = NULL;
	tmp = envp_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			path = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	if (path)
	{
		path_split = ft_split_without_quotes(path, ':');
		free(path);
		return (path_split);
	}
	return (NULL);
}

int	try_exec_command(char *cmd, char **command,
	char **envp, t_env *envp_list)
{
	char	**path;
	char	*tmp_cmd;

	path = get_path(envp_list);
	while (path && *path)
	{
		tmp_cmd = ft_strjoin(ft_strjoin(*path, "/"), cmd);
		if (execve(tmp_cmd, command, envp) != -1)
			return (0);
		free(tmp_cmd);
		path++;
	}
	return (-1);
}

void	execute_child_process(t_files *files, char **command,
	char **envp, t_env *envp_list)
{
	handle_redirection(files);
	if (!command || !command[0])
		exit(0);
	if (execve(command[0], command, envp) == -1
		&& try_exec_command(command[0], command, envp, envp_list) == -1)
	{
		write(2, command[0], ft_strlen(command[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

int	execute_command(t_files *files, char **command,
	char **envp, t_env *envp_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		execute_child_process(files, command, envp, envp_list);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
