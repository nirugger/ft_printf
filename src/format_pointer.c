/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 20:03:39 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:03:53 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

void	format_pointer(t_buffer *b, t_flags *flags, unsigned long ptr)
{
	int		i;
	int		len;

	flags->flags -= flags->flags & F_PREC;
	if (ptr == 0)
		return (format_string(b, flags, "(nil)"));
	i = 0;
	len = u_long_len(ptr, BASE_LO_HEX) + 2;
	if (flags->flags & F_MINUS)
	{
		fill_buffer(b, "0x", 2);
		u_long_copy_base(b, ptr, BASE_LO_HEX);
	}
	while (i < flags->width - len)
	{
		fill_buffer(b, " ", 1);
		i++;
	}
	if (!(flags->flags & F_MINUS))
	{
		fill_buffer(b, "0x", 2);
		u_long_copy_base(b, ptr, BASE_LO_HEX);
	}
}
