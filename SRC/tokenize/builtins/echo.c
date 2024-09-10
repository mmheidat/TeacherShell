/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:34:56 by mmheidat          #+#    #+#             */
/*   Updated: 2024/09/04 17:55:47 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		print_newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
}
