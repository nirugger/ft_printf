/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:58:41 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:06:48 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

int	ft_min(int a, int b)
{
	return (a * (a <= b) + b * (b < a));
}

int	ft_max(int a, int b)
{
	return (a * (a >= b) + b * (b > a));
}

int	ft_basic_atoi(const char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ft_is_digit(s[i]))
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (n);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
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
