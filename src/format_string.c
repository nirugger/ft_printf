/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 20:01:32 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:01:59 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

void	format_string(t_buffer *b, t_flags *flags, char *s)
{
	int		i;
	int		copy_len;

	i = 0;
	if (s == NULL)
	{
		s = "(null)";
		if (flags->precision < 6 && flags->flags & F_PREC)
			s = "";
	}
	copy_len = ft_strlen(s);
	if (flags->flags & F_PREC)
		copy_len = ft_min(copy_len, flags->precision);
	if (flags->flags & F_MINUS)
		fill_buffer(b, s, copy_len);
	while (i < flags->width - copy_len)
	{
		fill_buffer(b, " ", 1);
		i++;
	}
	if (!(flags->flags & F_MINUS))
		fill_buffer(b, s, copy_len);
	return ;
}
