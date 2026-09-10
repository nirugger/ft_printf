/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 15:44:17 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/10 20:29:07 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_flags		flags;
	t_buffer	buffer;

	if (!format)
		return (-1);
	va_start(args, format);
	ft_memset(&buffer, 0, sizeof(buffer));
	ft_memset(&flags, 0, sizeof(flags));
	while (format[flags.i])
		format_and_fill(format, &buffer, &flags, &args);
	put_buffer(&buffer);
	va_end(args);
	return (buffer.printed);
}

int	main(void)
{
	char	*string;

	string = "Hello 42!";
	ft_printf("%s\n", string);
	return (0);
}
