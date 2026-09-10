NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
MAGENTA	= \033[0;35m
CYAN	= \033[0;36m
WHITE	= \033[0;37m
RESET	= \033[0m

SRCS	= src/buffer.c \
		  src/checks.c \
		  src/flag_handler.c \
		  src/format_char.c \
		  src/format_digits.c \
		  src/format_hex.c \
		  src/format_pointer.c \
		  src/format_string.c \
		  src/format_unsigned.c \
		  src/ft_printf.c \
		  src/libft.c \
		  src/type_handler.c \
		  src/utils.c


OBJS = $(SRCS:.c=.o)

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "$(GREEN) libftprintf.a made ✓$(RESET)"

all: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)m$(RED)e$(GREEN)r$(RED)r$(GREEN)y $(RED)c$(GREEN)h$(RED)r$(GREEN)i$(RED)s$(GREEN)t$(RED)m$(GREEN)a$(RED)s$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	clear; $(RM) $(NAME) src/a.out
	@echo "$(GREEN)clean made ✓$(RESET)"

fclean:
	clear; $(RM)  $(OBJS); $(RM) $(NAME)
	@echo "$(GREEN)fclean made ✓✓✓$(RESET)"

re: clean $(NAME)
