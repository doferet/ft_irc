# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tronguye <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/12 13:45:32 by tronguye          #+#    #+#              #
#    Updated: 2026/04/12 13:45:39 by tronguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
BOT_NAME = ircbot

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp \
	Server.cpp \
	Client.cpp \
	Channel.cpp \
	Command/ACommand.cpp \
	Command/CommandFactory.cpp \
	Command/Pass.cpp \
	Command/Join.cpp \
	Command/Nick.cpp \
	Command/User.cpp

BOT_SRC = Bot.cpp

OBJ_DIR = obj

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

BOT_OBJ = $(BOT_SRC:%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bot: $(BOT_NAME)

$(BOT_NAME) : $(BOT_OBJ)
	$(CC) $(CFLAGS) $(BOT_OBJ) -o $(BOT_NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(BOT_NAME)

re: fclean all

.PHONY: all clean fclean re
