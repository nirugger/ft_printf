NAME = libftprintf.a
CC = cc
INCLUDE = libft
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE)
AR = ar rcs
RM = rm -f


SRC = src/format_digits.c \
	src/format_hex.c \
	src/format_unsigned.c \
	src/ft_memset.c \
	src/ft_printf.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) src/a.out

re: fclean all
