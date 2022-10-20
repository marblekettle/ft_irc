NAME = ircserv
CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = # SOURCE FILES GO HERE
OBJ = $(SRC:.cpp=.o)
HDIR = .

%.o: %.cpp
	$(CC) $(FLAGS) -I$(HDIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I$(HDIR) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
