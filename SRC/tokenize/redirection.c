/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:54:47 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/07 07:11:20 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	open_redirection_file(t_files *files)
{
	if (files->type == REDIRECT_IN)
		return (open(files->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (files->type == APPEND)
		return (open(files->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (files->type == REDIRECT_OUT)
		return (open(files->file_name, O_RDONLY));
	return (-1);
}

void	handle_fd_duplication(int fd, t_files *files)
{
	int	fd_dup;

	if (files->type == REDIRECT_OUT)
		fd_dup = 0;
	else
		fd_dup = 1;
	if (files->type != HEREDOC && fd >= 0)
		dup2(fd, fd_dup);
	else if (files->type != HEREDOC && fd < 0)
	{
		write(2, "Error opening file.\n", 20);
		exit(1);
	}
}

void	open_heredoc_first(t_files *files)
{
	while (files)
	{
		if (files->type == HEREDOC)
			handle_heredoc(files);
		files = files->next;
	}
}

void	handle_redirection(t_files *files)
{
	int	fd;

	while (files)
	{
		fd = open_redirection_file(files);
		handle_fd_duplication(fd, files);
		close(fd);
		files = files->next;
	}
}

// void	handle_heredoc(t_files *files)
// {
// 	char	*line;
// 	int		pipefd[2];

// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe");
// 		exit(1);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (line == NULL || ft_strcmp(line, files->file_name) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(pipefd[1], line, ft_strlen(line));
// 		write(pipefd[1], "\n", 1);
// 		free(line);
// 	}
// 	close(pipefd[1]);
// 	dup2(pipefd[0], 0);
// 	close(pipefd[0]);
// }

void	handle_heredoc(t_files *files)
{
	char	*line;
	int		pipefd[2];
	int		pid;

	if (pipe(pipefd) == -1)
		(perror("pipe"), exit(1));
	pid = fork();
	if (pid == -1)
		(perror("pipe"), exit(1));
	if (pid == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (line == NULL || ft_strcmp(line, files->file_name) == 0)
				(free(line), close(pipefd[1]), exit(0));
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
	}
	else
		(waitpid(pid, NULL, 0), close(pipefd[1]),
			dup2(pipefd[0], 0), close(pipefd[0]));
}
