/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 19:55:43 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 19:56:07 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

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
