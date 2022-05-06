/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:44:55 by kezekiel          #+#    #+#             */
/*   Updated: 2021/10/04 18:02:42 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	size_t	nlen;
	size_t	j;
	size_t	i;

	h = (char *)haystack;
	nlen = ft_strlen(needle);
	if (!(nlen))
		return (h);
	if (ft_strlen(haystack) < nlen || len < nlen)
		return (NULL);
	i = 0;
	while (h[i] && i <= len - nlen)
	{
		j = 0;
		while (needle[j] && needle[j] == h[i + j])
			j++;
		if (j == nlen)
			return (&h[i]);
		i++;
	}
	return (NULL);
}
