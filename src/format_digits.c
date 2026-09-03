/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 21:16:49 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 17:47:02 by nirugger         ###   ########.fr       */
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
int	ft_max(int a, int b)
{
	return (a * (a >= b) + b * (b > a));
}

int	get_id_format_len(t_flags *flags, int n)
{
	int	n_len;
	int	sign;

	sign = 0;
	if (n < 0 || flags->flags & F_PLUS || flags->flags & F_SPACE)
		sign = 1;
	n_len = int_len((long)n, BASE_TEN);
	printf("n_len = %d\nwidth = %d\n", n_len, flags->width);
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
	if (n < 0)
		fill_buffer(b, "-", 1);
	else if (flags->flags & F_PLUS)
		fill_buffer(b, "+", 1);
	else if (flags->flags & F_SPACE)
		fill_buffer(b, " ", 1);
	while (i < flags->precision - len)
	{
		fill_buffer(b, "0", 1);
		i++;
	}
	if (!(n == 0 && flags->precision == 0 && flags->flags & F_PREC))
		int_copy_base(b, (long)n, BASE_TEN);
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

	while (i < flags->width - ft_max(flags->precision, len))
	{
		if (flags->flags & F_ZERO && flags->precision > len)
			fill_buffer(b, "0", 1);
		else
			fill_buffer(b, " ", 1);
		i++;
	}
	if (!(flags->flags & F_MINUS))
		fill_buff_with_id(b, flags, n);
	return ;
}



// -: allineamento sinistro
// 0: padding con zeri a sinistra (se non c'è -)
//  : spazio prima di positivi se non usato +
// +: segno esplicito (+/-) per tutti i numeri
// #: nessun effetto su decimali nella maggior parte delle implementazioni
// Precisione: numero minimo di cifre (padding con 0)