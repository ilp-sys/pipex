NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm

SRCS = 
OBJS = 

all : $(NAME)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
