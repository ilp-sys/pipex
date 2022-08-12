NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAGS = -rf

LIBFT_DIR = libft/
LIBFT_LIB = libft.a

SRCS = main.c pipex_utils.c execute_cmd.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

clean : 
	@$(RM) $(RMFLAGS) $(OBJS)

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)

re: fclean all

bonus : all

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) all
	@$(CC) $(SRCS) $(LIBFT_DIR)$(LIBFT_LIB) -o $@

#%.o : %.c
$(OBJS) : $(SRCS)
	@$(CC) $(CFLAGS) $^ -c

.PHONY: all clean fclean re bonus
