/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirugger <nirugger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 16:29:11 by nirugger          #+#    #+#             */
/*   Updated: 2026/09/10 20:27:52 by nirugger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef FT_BUFSIZ
#  define FT_BUFSIZ	8192
# endif

# include <unistd.h>
# include <stdarg.h>

# define F_MINUS	1   // 1 << 0
# define F_ZERO		2   // 1 << 1
# define F_PREC		4   // 1 << 2
# define F_HASH		8   // 1 << 3
# define F_SPACE	16  // 1 << 4
# define F_PLUS		32  // 1 << 5

# define B_TEN		"0123456789"
# define B_HEX_LO	"0123456789abcdef"
# define B_HEX_UP	"0123456789ABCDEF"

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

// ----- BUFFER --------------------------------------------------------------
int		int_base_fill(t_buffer *b, long n, char *base);
int		ul_base_fill(t_buffer *b, unsigned long n, char *base);
void	put_buffer(t_buffer *b);
void	fill_buffer(t_buffer *b, const char *string, size_t n);
void	format_and_fill(const char *s, t_buffer *b, t_flags *f, va_list *a);

// ----- FLAGS ---------------------------------------------------------------
int		fill_flags(const char *format, t_flags *flags);
void	assign_flag(t_flags *flags, char c);
void	reset_flags(t_flags *flags);

// ----- TYPES ---------------------------------------------------------------
void	assign_type(t_flags *flags, char c);
void	type_router(t_buffer *b, t_flags *flags, va_list args);

// ----- FORMAT --------------------------------------------------------------
void	format_char(t_buffer *b, t_flags *flags, char c);
void	format_digits(t_buffer *b, t_flags *flags, int n);
void	format_hex(t_buffer *b, t_flags *flags, unsigned int n);
void	format_pointer(t_buffer *b, t_flags *flags, unsigned long ptr);
void	format_string(t_buffer *b, t_flags *flags, char *s);
void	format_unsigned(t_buffer *b, t_flags *flags, unsigned int n);
void	fill_width(t_buffer *b, t_flags *flags, int len);

// ----- LIBFT ---------------------------------------------------------------
int		ft_min(int a, int b);
int		ft_max(int a, int b);
int		ft_basic_atoi(const char *s);
int		ft_strlen(char *s);
void	*ft_memset(void *s, int c, size_t n);

// ----- UTILS ---------------------------------------------------------------
int		int_len(long n, char *base);
int		ul_len(unsigned long n, char *base);
long	l_base_pow_len(long n, long base_len);
long	ul_base_pow_len(unsigned long n, unsigned long base_len);

// ----- CHECKERS ------------------------------------------------------------
int		ft_is_digit(char c);
int		ft_is_type(char c);
int		ft_is_flag(char c);

#endif  //FT_PRINTF_H
