/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 17:55:23 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/10 18:43:04 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	assign_type(t_flags *flags, char c)
{
	if (c == 'c')
		flags->type = CHR;
	else if (c == 's')
		flags->type = STR;
	else if (c == 'p')
		flags->type = PTR;
	else if (c == 'd')
		flags->type = DIG;
	else if (c == 'i')
		flags->type = INT;
	else if (c == 'u')
		flags->type = US;
	else if (c == 'x')
		flags->type = L_X;
	else if (c == 'X')
		flags->type = U_X;
	else if (c == '%')
		flags->type = PERC;
}

void	type_router(t_buffer *b, t_flags *flags, va_list args)
{
	if (flags->type == CHR)
		format_char(b, flags, va_arg(args, int));
	else if (flags->type == STR)
		format_string(b, flags, va_arg(args, char *));
	else if (flags->type == PTR)
		format_pointer(b, flags, (unsigned long)va_arg(args, void *));
	else if (flags->type == INT || flags->type == DIG)
		format_digits(b, flags, va_arg(args, int));
	else if (flags->type == US)
		format_unsigned(b, flags, va_arg(args, unsigned int));
	else if (flags->type == L_X || flags->type == U_X)
		format_hex(b, flags, va_arg(args, unsigned int));
	else if (flags->type == PERC)
		fill_buffer(b, "%", 1);
	return ;
}
