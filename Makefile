##
## Makefile for plazza in /home/ju/tek/cpp/cpp_plazza
## 
## Made by ju
## Login   <ju@epitech.net>
## 
## Started on  Fri Apr 28 04:33:50 2017 ju
## Last update Sun Jun 18 22:13:11 2017 ju
##

CC		= g++ -g

RM		= rm -f

NAME		= indie_studio

INC_PATH	= inc

SRCS_PATH	= src
CORE_PATH	= $(SRCS_PATH)/core
OBJS_PATH	= $(SRCS_PATH)/objs

SRCS		= $(SRCS_PATH)/main.cpp \
		$(CORE_PATH)/RuntimeError.cpp \
		$(CORE_PATH)/Scene.cpp \
		$(CORE_PATH)/ScenesHandler.cpp \
		$(CORE_PATH)/Message.cpp \
		$(CORE_PATH)/Obj.cpp \
		$(CORE_PATH)/MessagesHandler.cpp \
		$(CORE_PATH)/EventReceiver.cpp \
		$(SRCS_PATH)/CreditsScene.cpp \
		$(SRCS_PATH)/Score.cpp \
		$(SRCS_PATH)/MainMenuScene.cpp \
		$(SRCS_PATH)/GameScene.cpp \
		$(SRCS_PATH)/MapEditorScene.cpp \
		$(SRCS_PATH)/OptionsScene.cpp \
		$(SRCS_PATH)/IntroScene.cpp \
		$(OBJS_PATH)/Map.cpp \
		$(OBJS_PATH)/Bomb.cpp \
		$(OBJS_PATH)/Player.cpp

OBJS		= $(SRCS:.cpp=.o)

CPPFLAGS	= -std=c++11 -W -Wall -Wextra -Werror -pthread
CPPFLAGS	+= -lIrrlicht -Llib
CPPFLAGS	+= -lGL -lXxf86vm -lXext -lX11 -lXcursor
CPPFLAGS	+= -I$(INC_PATH)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
