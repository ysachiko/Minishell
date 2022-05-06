/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:46:14 by kezekiel          #+#    #+#             */
/*   Updated: 2021/10/11 19:24:29 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	slen;
	unsigned int	nlen;

	if (s == NULL)
		return (NULL);
	slen = (unsigned int)ft_strlen((char *)s);
	nlen = (unsigned int)ft_strlen((char *)s + start);
	if (slen < start)
		return (ft_strdup(""));
	if (nlen < len)
		len = nlen;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s + start, len + 1);
	return (dst);
}
