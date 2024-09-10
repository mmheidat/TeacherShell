/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:04:02 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/05 22:41:16 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	sort_array(t_env **export_array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(export_array[j]->key, export_array[j + 1]->key) > 0)
				swap(export_array[j], export_array[j + 1]);
			j++;
		}
		i++;
	}
}

t_env	**list_array(t_env *env_list, int *size)
{
	t_env	*current;
	t_env	**array;
	int		i;

	if (!env_list)
		return (NULL);
	i = 0;
	current = env_list;
	*size = 0;
	while (current)
	{
		(*size)++;
		current = current->next;
	}
	array = malloc(sizeof(t_env *) * (*size));
	if (!array)
		return (NULL);
	current = env_list;
	while (current)
	{
		array[i++] = current;
		current = current->next;
	}
	return (array);
}

void	swap(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	tmp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_value;
}

void	print_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	if (!current)
		return ;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		else
			printf("%s\n", current->key);
		current = current->next;
	}
}

void	sort_and_print_export(t_env *env_list)
{
	int			size;
	t_env		**export_array;

	if (!env_list)
		return ;
	export_array = list_array(env_list, &size);
	if (export_array)
	{
		sort_array(export_array, size);
		print_export(*export_array);
		free(export_array);
	}
	else
		printf("Error\n");
}
