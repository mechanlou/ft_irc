NAME = server

HEADERS_DIR = headers

HEADERS =	ircserver.hpp
			# Channel.hpp

SRCS =	srcs/main.cpp \
		srcs/msg_handling.cpp \
		srcs/msg_sending.cpp
		# srcs/Channel.cpp \

OBJS = ${SRCS:.cpp=.o}

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS_DIR)/$(HEADERS)
	clang++ $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS_DIR)/$(HEADERS)
	clang++ -Wall -Wextra -Werror -std=c++98 -I$(HEADERS_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
