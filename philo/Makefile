SRCS = $(shell find . -name "*.c")
OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
CFLAGS = #-Wall -Wextra -Werror
INC = include/philosophers.h
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : %.c $(INC)
	@mkdir -p $(dir $@)
	cc $(CFLAGS) -c $< -o $@

clean :
	$(RM) -r $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean re

.PHONY: clean
