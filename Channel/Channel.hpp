#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#define string std::string

#include <vector>

class Channel
{
public:
    /* ----------------- Initialize ----------------- */
    Channel();
    Channel(string channelName, string key);
    Channel(const Channel &channel);
    Channel &operator=(const Channel &channel);
    Channel &operator==(const Channel &channel);

    /* ----------------- Setter Functions ----------------- */
    void SetChannelName(string channelName);
    void SetInviteOnly(bool inviteOnly);
    void SetKey(string password);
    void SetTopic(string topic);
    void SetMode(string mode);
    void SetIsPasswordProtected(bool isPasswordProtected);
    void SetUserCount(int userCount);
    void SetUserLimit(int userLimit);
    void SetOperator(string op);

    /* ----------------- Getter Functions ----------------- */
    string GetChannelName();
    string GetKey();
    string GetTopic();
    string GetMode();
    bool GetIsPasswordProtected();
    bool GetInviteOnly();
    int GetUserCount();
    int GetUserLimit();
    string GetOperator();
    
    std::vector<int> RegisteredUsersFd;
private:
    string _channelName;
    string _topic;
    string _mode;
    string _key;
    string _operator;
    int _userCount;
    int _userLimit;
    bool _isPasswordProtected;
    bool _inviteOnly;

};

#endif