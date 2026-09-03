/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 15:44:17 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 17:48:07 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

# include <stdio.h>

void	fill_buffer(t_buffer *b, const char *string, size_t n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		b->buff[b->now] = string[i];
		b->now++;
		i++;
		if (b->now == FT_BUFSIZ)
		{
			write(1, b->buff, FT_BUFSIZ);
			b->printed += FT_BUFSIZ;
			b->now = 0;
		}
	}
	return ;
}

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_type(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' ||
		c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int	ft_is_flag(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == ' ' || c == '+');
}

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

int	ft_basic_atoi(const char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ft_is_digit(s[i]))
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return (n);
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

void	format_char(t_buffer *b, t_flags *flags, char c)
{
	int		i;

	i = 0;
	if (flags->flags & F_MINUS)
		fill_buffer(b, &c, 1);
	while (i < flags->width - 1)
	{
		fill_buffer(b, " ", 1);
		i++;
	}
	if (!(flags->flags & F_MINUS))
		fill_buffer(b, &c, 1);
	return ;
}

int	ft_min(int a, int b)
{
	return (a * (a <= b) + b * (b < a));
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
	// printf("prec: %zu, prec flag: %i\n", copy_len, flags->flags & F_PREC);
	// getchar();
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

int	check_power(int n, int base_len)
{
	int	i;
	int	power;

	i = 0;
	power = 1;
	while (n > 0)
	{
		n /= base_len;
		i++;
	}
	while (i > 0)
	{
		power *= base_len;
		i--;
	}
	power /= base_len;
	return power;
}

int	int_copy_base(t_buffer *b, long n, char *base)
{
	int		base_len;
	long	power;
	char	c;
	int		char_count;

	char_count = 0;
	if (n == 0)
		return (fill_buffer(b, "0", 1), 1);
	if (n < 0)
		n *= -1;
	base_len = ft_strlen(base);
	power = check_power(n, base_len);
	while (power > 0)
	{
		c = base[n / power % base_len];
		fill_buffer(b, &c, 1);
		power /= base_len;
		char_count++;
	}
	return (char_count);
}

int	u_long_copy_base(t_buffer *b, long n, char *base)
{
	int		base_len;
	int		power;
	char	c;
	int		char_count;

	char_count = 0;
	if (n == 0)
		return (fill_buffer(b, "0", 1), 1);
	base_len = ft_strlen(base);
	power = check_power(n, base_len);
	while (power > 0)
	{
		c = base[n / power % base_len];
		fill_buffer(b, &c, 1);
		power /= base_len;
		char_count++;
	}
	return char_count;
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
		format_digits(b, flags, va_arg(args, int));




	else if (flags->type == PERC)
		fill_buffer(b, "%", 1);

	return ;
}

void	put_buff(t_buffer *b)
{
	write(1, b->buff, b->now);
	b->printed += b->now;
	b->now = 0;
	// write(1, "\n", 1);
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
			// getchar();
		}
	}
	put_buff(&b);
	va_end(args);
	return (b.printed);
}


int	main()
{
	t_buffer	b;
	ft_memset(&b, 0, sizeof(t_buffer));
	// num_copy_base(&b, t, "0123456789abcdef");
	// put_buff(&b);
	// ft_printf("%s\n", "ciaobabies");
	ft_printf(">% +010.5d<\n", 0);
	printf(">% +010.5d<\n", 0);
	// fill_buffer(&b, "ciaociaomiao", 12);
	// put_buff(&b);
	return (0);
}
// printf("flags: %d\ni: %lu\nprecision: %lu\ntype: %i\nwidth: %lu\n", flags.flags, flags.i, flags.precision, flags.type, flags.width);
