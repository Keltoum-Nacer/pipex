NAME = pipex
BNAME = pipex_bonus
CFILES = mandatory/main.c mandatory/pipex.c mandatory/pipe.c mandatory/pipex_utils_1.c mandatory/pipex_utils_2.c
OFILES = $(CFILES:.c=.o)
BCFILES = bonus/main_bonus.c bonus/pipex_bonus.c bonus/heredoc_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c bonus/multiple_pipes_bonus.c bonus/split_bonus.c bonus/utils_bonus.c
BOFILES	= $(BCFILES:.c=.o) 
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) 

bonus: $(BNAME)

$(BNAME): $(BOFILES)
	$(CC) $(CFLAGS) $(BOFILES) -o $(BNAME)

clean: 
	rm -f $(OFILES) $(BOFILES)

fclean: clean
	rm -f $(NAME)
re: fclean all

phony: all clean fclean re



