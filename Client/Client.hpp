#ifndef CLIENT_HPP
#define CLIENT_HPP

#define HEXCHAT 1
#define NC      0

#include "../Channel/Channel.hpp"

class Client
{
public:
    Client();
    Client(string nickname, string username, int fd);
    Client(Client const &client);
    Client &operator=(Client const &client);

    std::vector<Channel> RegisteredChannels;

    /* ----------------- Getter Functions ----------------- */
    int GetFd();
    bool GetRegistered();
    bool GetLoggedIn();
    bool GetConnectionType();
    string GetInvitedChannel();
    string GetUsername();
    string GetNickname();
    string GetIpAddress();
    string GetBuffer();
    string GetHostName();
    string GetClientColor();
    /* ----------------------------------------------------- */

    /* ----------------- Setter Functions ----------------- */
    void SetFd(int fd);
    void SetRegistered(bool isRegistered);
    void SetInvitedChannel(string channelName);
    void SetLoggedIn(bool isLoggedIn);
    void SetUsername(string username);
    void SetNickname(string nickname);
    void SetOldNickname(string oldNickname);
    void SetBuffer(string buffer);
    void SetIpAddress(string ipAddress);
    void SetClientColor(string clientColor);
    void SetConnectionType(bool connectionType);
    /* ----------------------------------------------------- */
    
    /* ----------------- Other Functions ----------------- */
    void ClearBuffer();
    /* ----------------------------------------------------- */

private:
    int _fd;
    int _registeredChannelCount;

    bool _isLoggedIn;
    bool _isOperator;
    bool _isRegistered;
    bool _connectionType;

    string _username;
    string _nickname;
    string _oldNickname;
    string _ipAddress;
    string _clientColor;
    string _buffer;
    string _hostName;
    string _invitedChannel;

    /* ----------------- Other Functions ----------------- */
    void CopyFrom(Client const &client);
    /* ----------------------------------------------------- */
};

#endif