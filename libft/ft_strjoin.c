/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmheidat <mmheidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:35:57 by mbamatra          #+#    #+#             */
/*   Updated: 2024/09/10 13:42:22 by mmheidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strcat(char *s1, const char *s2)
{
	size_t	i;
	size_t	h;

	i = 0;
	h = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	while (s2[h] != '\0')
	{
		s1[i] = s2[h];
		i++;
		h++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totallen;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	totallen = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(totallen + 1);
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	free((char *)s1);
	return (result);
}
