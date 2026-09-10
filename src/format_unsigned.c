/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 17:48:35 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/10 18:39:07 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	get_us_format_len(t_flags *flags, unsigned int n)
{
	int	n_len;
	int	zero;

	zero = 0;
	n_len = int_len((long)n, BASE_TEN);
	if (n == 0 && flags->precision == 0 && flags->flags & F_PREC)
		zero -= 1;
	return (ft_max(n_len, flags->precision) + zero);
}

static void	fill_buff_with_us(t_buffer *b, t_flags *flags, unsigned int n)
{
	int	len;
	int	i;

	len = int_len(n, BASE_TEN);
	i = 0;
	while (i < flags->precision - len)
	{
		fill_buffer(b, "0", 1);
		i++;
	}
	if (!(n == 0 && flags->precision == 0 && flags->flags & F_PREC))
		int_copy_base(b, (long)n, BASE_TEN);
	return ;
}

void	format_unsigned(t_buffer *b, t_flags *flags, unsigned int n)
{
	int		i;
	int		len;

	i = 0;
	len = get_us_format_len(flags, n);
	if (flags->flags & F_MINUS)
	{
		flags->flags -= flags->flags & F_ZERO;
		fill_buff_with_us(b, flags, n);
	}
	while (i < flags->width - ft_max(flags->precision, len))
	{
		fill_width(b, flags, len);
		i++;
	}
	if (!(flags->flags & F_MINUS))
		fill_buff_with_us(b, flags, n);
	return ;
}
