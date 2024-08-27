#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
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
    bool GetInvitedChannel(string &channelName);
    bool GetLoggedIn();
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
    void SetLoggedIn(bool isLoggedIn);
    void SetUsername(string username);
    void SetNickname(string nickname);
    void SetOldNickname(string oldNickname);
    void SetBuffer(string buffer);
    void SetIpAddress(string ipAddress);
    void SetClientColor(string clientColor);
    /* ----------------------------------------------------- */
    
    /* ----------------- Other Functions ----------------- */
    void ClearBuffer();
    void AddChannelInvite(string &channelName);
    void RemoveChannelInvite(string &channelName);
    /* ----------------------------------------------------- */

private:
    int _fd;
    int _registeredChannelCount;

    bool _isLoggedIn;
    bool _isOperator;
    bool _isRegistered;

    string _username;
    string _nickname;
    string _oldNickname;
    string _ipAddress;
    string _clientColor;
    string _buffer;
    string _hostName;
    std::vector<string> _channelsInvite;
};

#endif