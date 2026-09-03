/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 21:16:49 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:00:29 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

int	get_id_format_len(t_flags *flags, int n)
{
	int	n_len;
	int	sign;

	sign = 0;
	if (n < 0 || flags->flags & F_PLUS || flags->flags & F_SPACE)
		sign = 1;
	n_len = int_len((long)n, BASE_TEN);
	if (n == 0 && flags->precision == 0 && flags->flags & F_PREC)
		sign -= 1;
	return (ft_max(n_len, flags->precision) + sign);
}

void	fill_buff_with_id(t_buffer *b, t_flags *flags, int n)
{
	int	len;
	int	i;

	len = int_len(n, BASE_TEN);
	i = 0;
	if (flags->flags & F_PREC || !(flags->flags & F_ZERO))
	{
		if (n < 0)
			fill_buffer(b, "-", 1);
		else if (flags->flags & F_PLUS)
			fill_buffer(b, "+", 1);
		else if (flags->flags & F_SPACE)
			fill_buffer(b, " ", 1);
	}
	while (i < flags->precision - len)
	{
		fill_buffer(b, "0", 1);
		i++;
	}
	if (!(n == 0 && flags->precision == 0 && flags->flags & F_PREC))
		int_copy_base(b, (long)n, BASE_TEN);
}

void	fill_width(t_buffer *b, t_flags *flags, int len)
{
	if (flags->flags & F_PREC)
	{
		if (flags->flags & F_ZERO && flags->precision > len)
			fill_buffer(b, "0", 1);
		else
			fill_buffer(b, " ", 1);
	}
	else
	{
		if (flags->flags & F_ZERO && flags->width > len)
			fill_buffer(b, "0", 1);
		else
			fill_buffer(b, " ", 1);
	}
}

void	fill_sign(t_buffer *b, t_flags *flags, int n)
{
	char	sign;

	sign = '\0';
	if (!(flags->flags & F_PREC) && flags->flags & F_ZERO)
	{
		if (n < 0)
			sign = '-';
		else if (flags->flags & F_PLUS)
			sign = '+';
		else if (flags->flags & F_SPACE)
			sign = ' ';
	}
	if (sign)
		fill_buffer(b, &sign, 1);
}


void	format_digits(t_buffer *b, t_flags *flags, int n)
{
	int		i;
	int		len;

	i = 0;
	len = get_id_format_len(flags, n);
	if (flags->flags & F_MINUS)
	{
		flags->flags -= flags->flags & F_ZERO;
		fill_buff_with_id(b, flags, n);
	}
	fill_sign(b, flags, n);
	while (i < flags->width - ft_max(flags->precision, len))
	{
		fill_width(b, flags, len);
		i++;
	}
	if (!(flags->flags & F_MINUS))
		fill_buff_with_id(b, flags, n);
	return ;
}
