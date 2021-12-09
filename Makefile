NAME = test

HEADERS_FILE = headers

HEADERS = 

SRCS = srcs/main.cpp

OBJS = ${SRCS:.cpp=.o}

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	clang++ $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS)
	clang++ -Wall -Wextra -Werror -std=c++98 -I$(HEADERS_FILE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
