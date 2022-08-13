# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jiwahn <jiwahn@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/12 19:41:15 by jiwahn            #+#    #+#              #
#    Updated: 2022/08/13 14:33:38 by jiwahn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAGS = -rf

LIBFT_DIR = libft/
LIBFT_LIB = libft.a

SRCS = main.c pipex_utils.c execute_cmd.c \
	   get_next_line.c here_document.c

OBJ_DIR = obj/
OBJS = $(SRCS:.c=.o)

all : $(NAME)

clean : 
	@$(RM) $(RMFLAGS) $(OBJS)

fclean : clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(RMFLAGS) $(NAME)

re: fclean all

bonus : all

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) all
	@$(CC) $(SRCS) $(LIBFT_DIR)$(LIBFT_LIB) -o $@

$(OBJS) : $(SRCS)
	@$(CC) $(CFLAGS) $^ -c

.PHONY: all clean fclean re bonus
