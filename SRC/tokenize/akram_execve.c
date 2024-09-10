/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   akram_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:44:40 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 19:33:55 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	handle_exec_error(char *cmd, t_data *data)
{
	(void)data;
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	free_data(data);
	exit(127);
}

void	exec_command(t_cmd *cmd, char **envp, t_data *data, int *pip)
{
	char	**path;
	char	*tmp_cmd;

	close(pip[0]);
	if (cmd->next)
		dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
	if (check_built(cmd, *data) == 0)
		(check_current(cmd, *data), exit(0));
	handle_redirection(cmd->files);
	if (!cmd->content || !cmd->content[0])
		exit(0);
	if (execve(cmd->content[0], cmd->content, envp) == -1)
	{
		path = get_path(data->envp_list);
		while (path && *path)
		{
			tmp_cmd = ft_strjoin(ft_strjoin(*path, "/"), cmd->content[0]);
			if (execve(tmp_cmd, cmd->content, envp) != -1)
			{
				free(tmp_cmd);
				break ;
			}
			free(tmp_cmd);
			path++;
		}
		handle_exec_error(cmd->content[0], data);
	}
}

void	command_do(t_cmd *cmd, char **envp, t_data *data, int *tmd_fd)
{
	int		pip[2];

	while (cmd)
	{
		pipe(pip);
		open_heredoc_first(cmd->files);
		cmd->pid = fork();
		if (cmd->pid == -1)
			exit(1);
		if (cmd->pid == 0)
		{
			close(tmd_fd[0]);
			close(tmd_fd[1]);
			exec_command(cmd, envp, data, pip);
		}
		close(pip[1]);
		dup2(pip[0], STDIN_FILENO);
		close(pip[0]);
		cmd = cmd->next;
	}
}

void	akrm(t_cmd *cmd, char **envp, t_data *data, int *tmd_fd)
{
	t_cmd	*full_cmd;

	full_cmd = cmd;
	command_do(cmd, envp, data, tmd_fd);
	while (full_cmd)
	{
		waitpid(full_cmd->pid, &data->exit_status, 0);
		full_cmd = full_cmd->next;
		data->exit_status = WEXITSTATUS(data->exit_status);
	}
}
