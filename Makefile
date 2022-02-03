NAME = server

HEADERS_DIR = headers

HEADERS =	headers/Client.hpp \
			headers/Channel.hpp \
			headers/ircserver.hpp

SRCS =	srcs/main.cpp \
		srcs/utils.cpp \
		srcs/Client.cpp \
		srcs/Channel.cpp \
		srcs/msg_handling.cpp \
		srcs/msg_sending.cpp

OBJS = ${SRCS:.cpp=.o}

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	clang++ $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS)
	clang++ -Wall -Wextra -Werror -std=c++98 -I$(HEADERS_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
