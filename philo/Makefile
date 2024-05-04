SRCS = ./src/action/action.c ./src/action/eat.c ./src/action/sleep.c ./src/action/think.c ./src/action/utils.c \
	./src/main.c ./src/monitoring.c ./src/parse.c ./src/setup.c ./src/time.c \
	./utils/lst_addback.c ./utils/lst_addfront.c ./utils/lst_clear.c ./utils/lst_delone.c ./utils/lst_iter.c \
	./utils/lst_last.c ./utils/lst_new.c ./utils/lst_size.c
OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
CFLAGS = -Wall -Wextra -Werror 
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

re : fclean all

.PHONY: clean
