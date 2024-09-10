/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:41:50 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/05 11:04:22 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last_node;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_cmd_lstlast(*lst);
	if (last_node)
		last_node->next = new;
	else
		*lst = new;
}

t_cmd	*ft_cmd_lstlast(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*ft_cmd_lstnew(char	**content, t_files *files)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->files = files;
	new_node->next = NULL;
	return (new_node);
}

int	ft_cmd_lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
