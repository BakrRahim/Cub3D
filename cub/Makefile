NAME = pars
CFLAGS =  -Wall -Wextra -Werror 

SRCS =  get_next_line.c\
		main.c \
		pars.c\
		split.c\

OBJS = $(SRCS:.c=.o)
RM = rm -rf
CC = gcc

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME) 

clean :
	$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAME)

re : fclean all