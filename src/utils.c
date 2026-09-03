/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:56:22 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:06:28 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

int	int_len(long n, char *base)
{
	int	len;
	int	base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}


long	get_power_long(long n, long base_len)
{
	unsigned long	power;

	power = 1;
	while (n >= base_len)
	{
		n /= base_len;
		power *= base_len;
	}
	return power;
}

long	get_power_unsigned(unsigned long n, unsigned long base_len)
{
	unsigned long	power;

	power = 1;
	while (n >= base_len)
	{
		n /= base_len;
		power *= base_len;
	}
	return power;
}

int	u_long_len(unsigned long n, char *base)
{
	int	len;
	int	base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}
