/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:38:08 by mbamatra          #+#    #+#             */
/*   Updated: 2024/07/30 16:27:01 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;
	size_t	j;

	lensrc = ft_strlen(src);
	i = 0;
	j = 0;
	if (dstsize == 0)
		return (lensrc);
	while (dst[i] && i < dstsize)
		i++;
	lendst = i;
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[i - lendst];
		i++;
		j++;
	}
	if (lendst < dstsize)
		dst[i] = '\0';
	return (lendst + lensrc);
}
