/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:43:29 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/04 17:56:10 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	handle_cd_error(t_data *data, char *message)
{
	perror(message);
	data->exit_status = 1;
}

char	*get_cd_directory(t_cmd *cmd)
{
	if (cmd->content[1] == NULL)
		return (getenv("HOME"));
	return (cmd->content[1]);
}

void	cd(t_cmd *cmd, t_data *data)
{
	char	*dir;
	char	resolved_path[MAX_PATH_LEN];

	dir = get_cd_directory(cmd);
	if (dir == NULL)
	{
		handle_cd_error(data, "cd: HOME not set");
		return ;
	}
	if (resolve_directory(dir, resolved_path) != 0)
	{
		handle_cd_error(data, "cd: directory resolution error");
		return ;
	}
	if (chdir(resolved_path) != 0)
		handle_cd_error(data, "cd");
	else
		data->exit_status = 0;
}

int	resolve_directory(const char *path, char *resolved_path)
{
	if (realpath(path, resolved_path) == NULL)
	{
		return (-1);
	}
	return (0);
}
