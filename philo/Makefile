SRCS = ./src/action/action.c ./src/action/eat.c ./src/action/sleep.c ./src/action/think.c ./src/action/utils.c \
	./src/main.c ./src/monitoring.c ./src/parse.c ./src/setup.c ./src/time.c \
	./src/utils/lst_addback.c ./src/utils/lst_addfront.c ./src/utils/lst_clear.c ./src/utils/lst_delone.c ./src/utils/lst_iter.c \
	./src/utils/lst_last.c ./src/utils/lst_new.c ./src/utils/lst_size.c
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
