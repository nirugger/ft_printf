/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 15:44:17 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:07:53 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"


void	ft_assign_flag(t_flags *flags, char c)
{
	if (c == '-')
		flags->flags |= F_MINUS;
	else if (c == '0')
		flags->flags |= F_ZERO;
	else if (c == '.')
		flags->flags |= F_PREC;
	else if (c == '#')
		flags->flags |= F_HASH;
	else if (c == ' ')
		flags->flags |= F_SPACE;
	else if (c == '+')
		flags->flags |= F_PLUS;
}

void	ft_assign_type(t_flags *flags, char c)
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

int	fill_flags(const char *format, t_flags *flags)
{
	int	size;
	int	i;

	size = 0;
	i = flags->i + 1;
	while (ft_is_flag(format[i]))
	{
		ft_assign_flag(flags, format[i]);
		i++;
	}
	if (ft_is_digit(format[i]))
		flags->width = ft_basic_atoi(format + i);
	while (ft_is_digit(format[i]))
		i++;
	if (format[i] == '.')
	{
		ft_assign_flag(flags, '.');
		i++;
	}
	if (ft_is_digit(format[i]))
		flags->precision = ft_basic_atoi(format + i);
	while (ft_is_digit(format[i]))
		i++;
	if (ft_is_type(format[i]))
		ft_assign_type(flags, format[i]);
	else
		return (0);
	flags->i = i + 1;
	return (1);
}

void	reset_flags(t_flags *flags)
{
	flags->flags = 0;
	flags->precision = 0;
	flags->type = 0;
	flags->width = 0;
}


void	route_type(t_buffer *b, t_flags *flags, va_list args)
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

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_flags		flags;
	t_buffer	b;

	if (!format)
		return (-1);

	va_start(args, format);
	ft_memset(&b, 0, sizeof(b));
	ft_memset(&flags, 0, sizeof(flags));

	while (format[flags.i])
	{
		if (format[flags.i] != '%')
		{
			fill_buffer(&b, format + flags.i, 1);
			flags.i++;
		}
		else
		{
			if (fill_flags(format, &flags))
			{
				route_type(&b, &flags, args);
			}
			else
			{
				fill_buffer(&b, format + flags.i, 1);
				flags.i++;
			}
			reset_flags(&flags);
		}
	}
	put_buffer(&b);
	va_end(args);
	return (b.printed);
}


// int	main()
// {
// 	t_buffer	b;
// 	char *s = (char *)-1;
// 	ft_memset(&b, 0, sizeof(t_buffer));


// 	// ft_printf(">%p<\n\n", s);
// 	// printf(">%p<\n\n", s);
// 	ft_printf(">%20d<\n", -42000);
// 	printf(">%20d<\n", -42000);
// 	// ft_printf("%+040d\n", 11);
// 	// printf("%+040d\n", 11);
// 	return (0);
// }
