/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 20:31:19 by mbamatra          #+#    #+#             */
/*   Updated: 2024/07/30 16:27:01 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*destination;
	char	*source;
	size_t	i;

	if (src == NULL && dst == NULL)
		return (NULL);
	if (!n)
		return (dst);
	destination = (char *)dst;
	source = (char *)src;
	i = 0;
	while (n > i)
	{
		destination[i] = source[i];
		i++;
	}
	return (dst);
}
