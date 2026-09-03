/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 16:29:11 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/03 18:32:27 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FT_BUFSIZ
#  define FT_BUFSIZ 8
# endif

# include <unistd.h>
# include <stdarg.h>


# define F_MINUS 1
# define F_ZERO 1 << 1
# define F_PREC 1 << 2
# define F_HASH 1 << 3
# define F_SPACE 1 << 4
# define F_PLUS 1 << 5

# define BASE_TEN "0123456789"
# define BASE_LO_HEX "0123456789abcdef"
# define BASE_UP_HEX "0123456789ABCDEF"

typedef struct s_buffer	t_buffer;
typedef struct s_flags	t_flags;
typedef enum e_types	t_types;

enum e_types
{
	CHR,
	STR,
	PTR,
	DIG,
	INT,
	US,
	L_X,
	U_X,
	PERC,
};

struct s_buffer
{
	char	buff[FT_BUFSIZ];
	int		now;
	int		printed;
};

struct s_flags
{
	char	flags;
	int		width;
	int		precision;
	t_types	type;
	size_t	i;
};

int		ft_printf(const char *format, ...);
void	fill_buffer(t_buffer *b, const char *string, size_t n);
int		int_copy_base(t_buffer *b, long n, char *base);
void	format_unsigned(t_buffer *b, t_flags *flags, unsigned int n);
int		int_len(long n, char *base);
void	format_hex(t_buffer *b, t_flags *flags, unsigned int n);
void	fill_width(t_buffer *b, t_flags *flags, int len);

void	format_digits(t_buffer *b, t_flags *flags, int n);
int		ft_strlen(char *s);
int		ft_max(int a, int b);
void	*ft_memset(void *buff, int c, size_t n);

#endif //FT_PRINTF_H
