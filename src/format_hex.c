/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 18:13:11 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/10 20:16:05 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_hex_format_len(t_flags *flags, unsigned int n)
{
	int	n_len;
	int	sign;

	sign = 0;
	if (flags->flags & F_HASH)
		sign += 2;
	n_len = int_len((long)n, B_HEX_LO);
	return (ft_max(n_len, flags->precision) + sign);
}

static void	fill_buff_with_hex(t_buffer *b, t_flags *flags, unsigned int n)
{
	int	len;
	int	i;

	len = int_len(n, B_HEX_LO);
	i = 0;
	if (flags->flags & F_HASH && flags->type == L_X)
		fill_buffer(b, "0x", 2);
	if (flags->flags & F_HASH && flags->type == U_X)
		fill_buffer(b, "0X", 2);
	while (i < flags->precision - len)
	{
		fill_buffer(b, "0", 1);
		i++;
	}
	if (flags->type == L_X)
		int_base_fill(b, (long)n, B_HEX_LO);
	else
		int_base_fill(b, (long)n, B_HEX_UP);
	return ;
}

void	format_hex(t_buffer *b, t_flags *flags, unsigned int n)
{
	int		i;
	int		len;

	i = 0;
	len = get_hex_format_len(flags, n);
	if (n == 0)
		return (format_unsigned(b, flags, n));
	if (flags->flags & F_MINUS)
	{
		flags->flags -= flags->flags & F_ZERO;
		fill_buff_with_hex(b, flags, n);
	}
	while (i < flags->width - ft_max(flags->precision, len))
	{
		fill_width(b, flags, len);
		i++;
	}
	if (!(flags->flags & F_MINUS))
		fill_buff_with_hex(b, flags, n);
	return ;
}
