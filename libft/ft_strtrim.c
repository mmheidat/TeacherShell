/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbamatra <mbamatra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:45:38 by mbamatra          #+#    #+#             */
/*   Updated: 2024/07/30 16:27:01 by mbamatra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size_s1;

	if (s1 == NULL || set == NULL)
		return (ft_strdup(""));
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size_s1 = ft_strlen(s1);
	while (ft_strchr(set, s1[size_s1]) && size_s1 != 0)
		size_s1--;
	return (ft_substr(s1, 0, size_s1 + 1));
}
