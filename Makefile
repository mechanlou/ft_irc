NAME = ircserv

HEADERS_DIR = headers

HEADERS =	headers/Client.hpp \
			headers/Channel.hpp \
			headers/parser.hpp \
			headers/reply_codes.hpp \
			headers/reply_functions.hpp \
			headers/commands/KICK.hpp \
			headers/commands/NICK.hpp \
			headers/commands/PART.hpp \
			headers/commands/PRIVMSG.hpp \
			headers/commands/TOPIC.hpp \
			headers/commands/JOIN.hpp \
			headers/commands/LIST.hpp \
			headers/commands/NAMES.hpp \
			headers/commands/NOTICE.hpp \
			headers/commands/PASS.hpp \
			headers/commands/QUIT.hpp \
			headers/commands/USER.hpp \
			headers/commands/commands.hpp \
			headers/ircserver.hpp

SRCS =	srcs/main.cpp \
		srcs/utils.cpp \
		srcs/Client.cpp \
		srcs/Channel.cpp \
		srcs/msg_handling.cpp \
		srcs/parser.cpp \
		srcs/commands/command.cpp \
		srcs/commands/JOIN.cpp \
		srcs/commands/KICK.cpp \
		srcs/commands/LIST.cpp \
		srcs/commands/NAMES.cpp \
		srcs/commands/NICK.cpp \
		srcs/commands/NOTICE.cpp \
		srcs/commands/PART.cpp \
		srcs/commands/PASS.cpp \
		srcs/commands/PRIVMSG.cpp \
		srcs/commands/QUIT.cpp \
		srcs/commands/TOPIC.cpp \
		srcs/commands/USER.cpp \
		srcs/rpl_reply_functions.cpp \
		srcs/err_reply_functions.cpp \
		srcs/msg_sending.cpp

OBJS = ${SRCS:.cpp=.o}

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	clang++ $(OBJS) -o $(NAME)

$(OBJS): %.o: %.cpp $(HEADERS)
	clang++ -Wall -Wextra -Werror -I$(HEADERS_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
