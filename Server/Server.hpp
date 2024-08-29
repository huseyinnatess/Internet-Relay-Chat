#ifndef SERVER_HPP
#define SERVER_HPP

#include "../Client/Client.hpp"
#include "../Print/Print.hpp"
#include "../Error/Error.hpp"
#include <vector>
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <map> //-> for std::map

enum Commands
{
    BONG,
    PASS,
    NICK,
    USER,
    QUIT,
    KICK,
    JOIN,
    TOPIC,
    MODE,
    PART,
    PRIVMSG,
    INVITE
};

class Server
{
public:
    Server(){_socketFd = -1;}
    Server(const Server& server);
    Server& operator=(const Server& server);

    void ServerInit(int port, string password);
    void ServerCreateSocket();
    void AcceptNewClient();
    void ReceiveNewData(int fd); // Receive data from a registered client
    void SetClosedClientDefaultValue(int fd);

    static void SignalHandler(int signal);

    void CloseFds(); // Close all file descriptors
    void ClearClients(int fd); // Clear all clients
    std::vector<Client> Clients;

    Client& GetClient(int fd);

private:
    int _port;
    int _socketFd;
    
    static bool _signal;

    std::vector<struct pollfd> _pollFds; // Multiple file descriptors can be monitored at once
    string _password;
    std::map<string, Commands> _commandsMap;
    std::vector<Channel> CreatedChannels;


    /* ----------------- Initialize Functions ----------------- */
    void InitializeCommandMap();
    void ConfigureSocket(int _socketFd, struct sockaddr_in serverAddr);
    void ServerLoop();

    /* ----------------- Parser, Router Functions ----------------- */
    void RouterLoginCommands(int fd, int commandIndex, std::vector<string> command);
    void RouterCommands(int fd, int commandIndex, std::vector<string> command);
    void ParseClientCommands(int fd, string command);
    int FindCommandInMap(string command);

    /* ----------------- Command Functions ----------------- */
    void ClientAutherization(int fd, std::vector<string> command); // PASS
    void ClientNick(int fd, std::vector<string> command); // NICK
    void ClientUsername(int fd, std::vector<string> command); // USER
    void ClientQuit(int fd); // QUIT
    void ClientJoin(int fd, std::vector<string>& channelNames); // JOIN
    void ClientPart(int fd, std::vector<string>& channelNames); // PART

    /* ----------------- Check Functions ----------------- */
    bool CheckIsUsing(string value, string checkValue);
    int  CheckClientRegistered(int fd, string channelName);
    void ShowChannelInformations(int fd, string channelName);
    
    /* ----------------- Error Functions ----------------- */
    void SendError(int fd, string errorMesssage, int clientCloseFlag = 0);

    /* ----------------- Message Functions ----------------- */
    void SendMessage(int fd, string message);
    void SendAllClientsMessage(std::vector<int> fds, string message);

    /* ----------------- Channel Functions ----------------- */
    int CheckChannelIsCreated(string channelName);
    int GetCreatedChannelIndex(string channelName);
    void JoinChannel(int fd, string channelName, int index);
    void CreateAndJoinChannel(int fd, string channelName, string key);
    std::vector<string> SplitChannelNames(std::vector<string> channelNames);
    void RemoveChannel(int channelIndex);
    void RemoveChannelFromClient(int fd, string channelName);
    void RemoveChannelRegisteredUser(int fd, string channelName);

};


#endif