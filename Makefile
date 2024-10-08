NAME = ircserv

PRINT = ./Print
SERVER = ./Server
CLIENT = ./Client
COMMANDS = ./Commands
CHANNEL = ./Channel
MESSAGE = ./MESSAGE
CHECK = ./Check
CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRC =	SERVER/Server.cpp \
		SERVER/AcceptClient.cpp \
		SERVER/CreateSocket.cpp \
		SERVER/SignalHandler.cpp \
		SERVER/CloseAndClear.cpp \
		SERVER/ReceiveNewData.cpp \
		SERVER/GetFunctions.cpp \
		SERVER/ParseClientCommand.cpp \
		SERVER/Remove.cpp \
		CLIENT/Client.cpp \
		CLIENT/GetFunctions.cpp \
		CLIENT/SetFunctions.cpp \
		COMMANDS/Commands.cpp \
		COMMANDS/CAP.cpp \
		COMMANDS/PASS.cpp \
		COMMANDS/NICK.cpp \
		COMMANDS/USER.cpp \
		COMMANDS/QUIT.cpp \
		COMMANDS/JOIN.cpp \
		COMMANDS/PART.cpp \
		COMMANDS/TOPIC.cpp \
		COMMANDS/MODE.cpp \
		COMMANDS/INVITE.cpp \
		COMMANDS/KICK.cpp \
		COMMANDS/PRIVMSG.cpp \
		COMMANDS/NOTICE.cpp \
		CHANNEL/Channel.cpp \
		CHANNEL/GetFunctions.cpp \
		CHANNEL/SetFunctions.cpp \
		MESSAGE/Message.cpp \
		CHECK/CommandsCheck.cpp \
		PRINT/Print.cpp \
		main.cpp

OBJDIR = Output

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)


$(OBJDIR)/%.o : %.cpp
	@mkdir -p $(dir $@)
	@$(CPP) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CPP) $(FLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
