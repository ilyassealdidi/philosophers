SRCS = $(shell find . -name "*.c")
OBJS = $(SRCS:.c=.o)
CFLAGS = #-Wall -Wextra -Werror
INC = include/philosophers.h
NAME = philo
#! Create objects in a seperated folder
all : $(NAME)

$(NAME) : $(OBJS)
	cc $(OBJS) -o $(NAME)

%.o : %.c $(INC)
	cc $(CFLAGS) -c $< -o $@

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean re

.PHONY: clean