SRCS = src/action.c src/main.c src/monitoring.c src/parse.c src/setup.c \
	src/utils/time.c src/utils/error.c src/utils/utils.c src/utils/mutex.c \
	src/utils/thread.c \
	src/utils/linked_list/lst_addback.c src/utils/linked_list/lst_addfront.c \
	src/utils/linked_list/lst_clear.c src/utils/linked_list/lst_delone.c \
	src/utils/linked_list/lst_iter.c src/utils/linked_list/lst_last.c \
	src/utils/linked_list/lst_new.c src/utils/linked_list/lst_size.c
OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
CFLAGS = -Iinclude -Wall -Wextra -Werror
INC = include/philosophers.h include/types.h
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	cc -g  $(OBJS) -o $(NAME)

$(OBJS_DIR)%.o : %.c $(INC)
	@mkdir -p $(dir $@)
	@cc -g  $(CFLAGS) -c $< -o $@

clean :
	$(RM) -r $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all
