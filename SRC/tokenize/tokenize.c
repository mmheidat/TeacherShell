/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:55:36 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 19:13:32 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	size_of_content(char **splitted)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (splitted[i])
	{
		if (splitted[i][0] == '>' || splitted[i][0] == '<')
			i++;
		else
			size++;
		i++;
	}
	return (size);
}

void	process_split_part(char **splitted, t_files **files, char **the_cmd)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	while (splitted[j])
	{
		if (splitted[j][0] == '>' || splitted[j][0] == '<')
		{
			ft_files_lstaddback(files,
				ft_file_lstnew(splitted[j + 1], splitted[j]));
			j++;
		}
		else
			the_cmd[n++] = ft_strdup(splitted[j]);
		j++;
	}
	the_cmd[n] = NULL;
}

t_cmd	*fill_command(char **split)
{
	t_cmd		*cmd;
	t_files		*files;
	char		**splitted;
	char		**the_cmd;
	int			i;

	cmd = NULL;
	i = 0;
	if (!split)
		return (NULL);
	while (split[i])
	{
		files = NULL;
		splitted = ft_split_without_quotes(split[i], ' ');
		if (!splitted)
		{
			free_split_memory(split, i);
			return (NULL);
		}
		the_cmd = (char **)malloc(sizeof(char *)
				* (size_of_content(splitted) + 1));
		if (!the_cmd)
			return (NULL);
		process_split_part(splitted, &files, the_cmd);
		free_double_pointer(splitted);
		ft_cmd_lstadd_back(&cmd, ft_cmd_lstnew(the_cmd, files));
		cmd->pid = 0;
		i++;
	}
	return (cmd);
}
