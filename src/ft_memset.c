/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 18:37:27 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/02 17:30:51 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"


void	*ft_memset(void *s, int c, size_t n)
{
	int	i;
	unsigned char	*buff;

	if (!s)
		return (s);
	i = 0;
	buff = (unsigned char *)s;
	while (i < n)
	{
		buff[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
