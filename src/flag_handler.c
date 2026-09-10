/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 17:53:53 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/10 18:58:43 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	assign_flag(t_flags *flags, char c)
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

int	fill_flags(const char *format, t_flags *flags)
{
	int	size;
	int	i;

	size = 0;
	i = flags->i + 1;
	while (ft_is_flag(format[i]))
		assign_flag(flags, format[i++]);
	if (ft_is_digit(format[i]))
		flags->width = ft_basic_atoi(format + i);
	while (ft_is_digit(format[i]))
		i++;
	if (format[i] == '.')
	{
		assign_flag(flags, '.');
		i++;
	}
	if (ft_is_digit(format[i]))
		flags->precision = ft_basic_atoi(format + i);
	while (ft_is_digit(format[i]))
		i++;
	if (!ft_is_type(format[i]))
		return (0);
	assign_type(flags, format[i]);
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
