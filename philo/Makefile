SRCS = src/action/action.c src/action/eat.c src/action/sleep.c src/action/think.c src/action/utils.c \
	src/main.c src/monitoring.c src/parse.c src/setup.c \
	src/utils/time.c src/utils/error.c src/utils/utils.c \
	src/utils/linked_list/lst_addback.c src/utils/linked_list/lst_addfront.c \
	src/utils/linked_list/lst_clear.c src/utils/linked_list/lst_delone.c \
	src/utils/linked_list/lst_iter.c src/utils/linked_list/lst_last.c \
	src/utils/linked_list/lst_new.c src/utils/linked_list/lst_size.c
OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
CFLAGS = -Iinclude -Wall -Wextra -Werror
INC = include/philosophers.h include/types.h include/utils.h
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
