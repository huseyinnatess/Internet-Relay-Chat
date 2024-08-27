NAME = ircserv

PRINT = ./Print
SERVER = ./Server
CLIENT = ./Client
COMMANDS = ./Commands
CHANNEL = ./Channel
ERROR = ./Error

SRC =	SERVER/Server.cpp \
		SERVER/AcceptClient.cpp \
		SERVER/CreateSocket.cpp \
		SERVER/SignalHandler.cpp \
		SERVER/CloseAndClear.cpp \
		SERVER/ReceiveNewData.cpp \
		SERVER/GetFunctions.cpp \
		SERVER/ParseClientCommand.cpp \
		CLIENT/Client.cpp \
		CLIENT/GetFunctions.cpp \
		CLIENT/SetFunctions.cpp \
		COMMANDS/Commands.cpp \
		COMMANDS/PASS.cpp \
		COMMANDS/NICK.cpp \
		COMMANDS/USER.cpp \
		COMMANDS/QUIT.cpp \
		COMMANDS/JOIN.cpp \
		COMMANDS/PART.cpp \
		CHANNEL/Channel.cpp \
		CHANNEL/GetFunctions.cpp \
		CHANNEL/SetFunctions.cpp \
		ERROR/Error.cpp \
		PRINT/Print.cpp \
		CheckArguments.cpp \
		main.cpp

OBJDIR = Output

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

CPP = c++
FLAGS = -std=c++98 -g

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
