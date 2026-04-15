# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doferet <doferet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/12 13:45:32 by tronguye          #+#    #+#              #
#    Updated: 2026/04/15 10:15:02 by doferet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
BOT_NAME = ircbot

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRC = main.cpp \
	Server.cpp \
	Client.cpp \
	Channel.cpp \
	Command/ACommand.cpp \
	Command/CommandFactory.cpp \
	Command/Pass.cpp \
	Command/Join.cpp \
	Command/Nick.cpp \
	Command/User.cpp \
	Command/Ping.cpp \
	Command/Mode.cpp \
	Command/Privmsg.cpp \
	Command/Part.cpp \
	Command/Quit.cpp \
	Command/Topic.cpp \
	Command/Kick.cpp \
	Command/Invite.cpp \

BOT_SRC = Bot.cpp \

OBJ_DIR = obj

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

BOT_OBJ = $(BOT_SRC:%.cpp=$(OBJ_DIR)/%.o)

all: $(NAME) $(BOT_NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bot: $(BOT_NAME)

$(BOT_NAME) : $(BOT_OBJ)
	$(CC) $(CFLAGS) $(BOT_OBJ) -o $(BOT_NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(BOT_NAME)

re: fclean all

.PHONY: all clean fclean re
