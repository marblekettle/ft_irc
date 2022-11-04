<<<<<<< HEAD
NAME		=	ircserv
=======
NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -std=c++98
SRC = 		main.cpp \
			Server.cpp \
			ClientAttr.cpp \
			ServerAttr.cpp \
			Channel.cpp	
>>>>>>> b2e3e107faa7d08efc8f515e8162d5411a1c6054

SRC_DIR		=	src/
HEADER_DIR	=	include/
OBJ_DIR		=	obj/
BIN_DIR		=	bin/
BIN			=	$(BIN_DIR)$(NAME)

SRC			=	Server.cpp \
				ServerAttr.cpp \
				Client.cpp \
				Channel.cpp \
				Command.cpp \
				JoinCommand.cpp \
				SendMessageCommand.cpp \
				main.cpp \

HEADERS		=	Server.hpp \
				ServerAttr.hpp \
				Client.hpp \
				Channel.hpp \
				Command.hpp \
				JoinCommand.hpp \
				SendMessageCommand.hpp \

OBJ 		=	$(addprefix $(OBJ_DIR), $(SRC:%.cpp=%.o))

INCL_DIRS	=	$(HEADER_DIR)
INCLUDES	=	$(addprefix -I, $(INCL_DIRS))

CFLAGS		=	-Wall -Werror -Wextra -std=c++98 -pedantic # -g -fsanitize=address
CC			=	c++

ifeq ("$(VERBOSE)","1")
Q :=
VECHO = @echo
else
Q := @
VECHO = @echo
endif

all: $(BIN)

$(BIN): $(OBJ)
	$(Q)mkdir -p $(@D)
	$(VECHO)
	$(VECHO) "\033[36mLinking binary file:     \033[0m$@ 🚨"
	$(VECHO)
	$(Q)$(CC) $^ $(CFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(addprefix $(HEADER_DIR), $(HEADERS))
	$(Q)mkdir -p $(@D)
	$(VECHO) "\033[34mCompiling object file:   \033[0m$@"
	$(Q)$(CC) -c $< $(CFLAGS) -o $@ $(INCLUDES)

clean:
	$(VECHO) "\033[31mRemoving object files\033[0m"
	$(VECHO)
	$(Q)rm -rf $(OBJ_DIR)

fclean: clean
	$(VECHO) "\033[31mRemoving binary\033[0m"
	$(VECHO)
	$(Q)rm -f $(BIN)

re: clean all

.PHONY:	all clean fclean re
