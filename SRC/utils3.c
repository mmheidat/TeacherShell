/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 06:27:59 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 19:58:35 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	check_built(t_cmd *cmd, t_data data)
{
	(void)data;
	if (ft_strcmp(cmd->content[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "export") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "clear") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "env") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd->content[0], "unset") == 0)
		return (0);
	return (1);
}

int	check_current_in_pipe(t_cmd *cmd, t_data data)
{
	if (ft_strcmp(cmd->content[0], "exit") == 0)
		(printf("exit\n"), exit(0));
	else if (ft_strcmp(cmd->content[0], "export") == 0)
		return (export(&data, cmd), 0);
	else if (ft_strcmp(cmd->content[0], "clear") == 0)
		return (system("clear"), 0);
	else if (ft_strcmp(cmd->content[0], "env") == 0)
		return (add_temp_env(&data, cmd), 0);
	else if (ft_strcmp(cmd->content[0], "cd") == 0)
		return (cd(cmd, &data), 0);
	else if (ft_strcmp(cmd->content[0], "echo") == 0)
		return (ft_echo(cmd->content), 0);
	else if (ft_strcmp(cmd->content[0], "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(cmd->content[0], "unset") == 0)
		return (remove_env(&data.export_list, cmd),
			remove_env(&data.envp_list, cmd), 0);
	return (1);
}



void	free_cmd_content(char **content)
{
	int	i;

	if (!content)
		return ;
	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
}

void	free_cmd_memory(t_cmd **cmd)
{
	t_cmd	*temp;

	while (*cmd)
	{
		temp = (*cmd)->next;
		free_cmd_content((*cmd)->content);
		free_files((*cmd)->files);
		free(*cmd);
		*cmd = temp;
	}
	*cmd = NULL;
}
