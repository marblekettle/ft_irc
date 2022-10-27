NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = 		main.cpp \
			Server.cpp \
			ClientAttr.cpp \
			ServerAttr.cpp \
			Channel.cpp	

SRCDIR = src/
OBJ = $(SRC:.cpp=.o)
HDIR = include

%.o: $(SRCDIR)%.cpp
	$(CC) $(FLAGS) -I$(HDIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I$(HDIR) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
