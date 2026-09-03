/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 20:02:50 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 20:07:46 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"


void	put_buffer(t_buffer *b)
{
	write(1, b->buff, b->now);
	b->printed += b->now;
	b->now = 0;
}

void	fill_buffer(t_buffer *b, const char *string, size_t n)
{
	size_t	i;

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

int	int_copy_base(t_buffer *b, long n, char *base)
{
	int		base_len;
	unsigned long	power;
	char	c;
	int		char_count;

	char_count = 0;
	if (n == 0)
		return (fill_buffer(b, "0", 1), 1);
	if (n < 0)
		n *= -1;
	base_len = ft_strlen(base);
	power = get_power_long(n, (long)base_len);
	while (power > 0)
	{
		c = base[n / power % base_len];
		fill_buffer(b, &c, 1);
		power /= base_len;
		char_count++;
	}
	return (char_count);
}

int	u_long_copy_base(t_buffer *b, unsigned long n, char *base)
{
	int		base_len;
	unsigned long	power;
	char	c;
	int		char_count;

	char_count = 0;
	if (n == 0)
	return (fill_buffer(b, "0", 1), 1);
	base_len = ft_strlen(base);
	power = get_power_unsigned(n, (unsigned long)base_len);
	while (power > 0)
	{
		c = base[n / power % base_len];
		fill_buffer(b, &c, 1);
		power /= base_len;
		char_count++;
	}
	return char_count;
}
