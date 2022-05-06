/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:08:33 by kezekiel          #+#    #+#             */
/*   Updated: 2021/10/11 16:44:58 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	const char		*b;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	a = dst;
	b = src;
	while (n > i)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
