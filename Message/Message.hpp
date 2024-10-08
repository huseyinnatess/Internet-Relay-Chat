#ifndef ERROR_HPP
#define ERROR_HPP

/* -------------------- GENERAL ERROR MESSAGES -------------------- */
#define ERR_NEEDMOREPARAMS(command)			            ": 461 " + command + " :Not enough parameters" + "\r\n"              //MODE
#define ERR_NOSUCHCHANNEL(channelName)			        ": 403 " + channelName + " :No such channel" + "\r\n"
#define ERR_NOTREGISTERED(nick)				            ": 451 " + nick + " :You have not registered\r\n"

/* -------------------- PASS ERROR MESSAGES -------------------- */
#define ERR_PASSWDMISMATCH                              ":Password incorrect\r\n"

/* -------------------- USER ERROR MESSAGES -------------------- */
#define ERR_ALREADYREGISTRED                            ": 462 :You may not reregister\r\n"
#define ERR_CANNOTCHANGEUSERNAME(nick)                   ": 503 " + nick + " :You may not change your username\r\n"
#define ERR_NONICKNAME                                     " Nickname should be entered firstly \r\n"
/* -------------------- NICK ERROR MESSAGES -------------------- */
#define ERR_ERRONEUSNICKNAME(nick)			            ": 432 " + nick + " :Erroneus nickname" + "\r\n"                      //NICK
#define ERR_NICKNAMEINUSE(nick)				            ": 433 " + nick + " :Nickname is already in use" + "\r\n"              //NICK
#define ERR_NONICKNAMEGIVEN                             ": 431 :No nickname given\r\n"                                      //NICK

/* -------------------- JOIN ERROR MESSAGES -------------------- */
#define RPL_JOIN(nick, ip, channel)					    ":" + nick + "!" + nick + "@" + ip + " JOIN " + channel + "\r\n"
#define ERR_CHANNELISFULL(channel)					    ": 471 " + channel + " :Cannot join channel (+l)\r\n"

/* -------------------- PART ERROR MESSAGES -------------------- */
#define ERR_NOTONCHANNEL(channelName)				    ": 442 " + channelName + " :You're not on that channel\r\n"
#define RPL_PART(nick, channel)						    ":" + nick + " PART " + channel + "\r\n"

/* -------------------- INFORMATION MESSAGES -------------------- */
#define RPL_TOPIC(nick, ip, channel, topic)             ":" + nick + "!" + nick + "@" + ip + " TOPIC " + channel + " :" + topic + "\r\n"       
#define RPL_NOTOPIC(nick, channel)                      ": 331 " + nick + " " + channel + " :No topic is set" + "\r\n"
#define RPL_NAMREPLY(nick, channel, users)			    ": 353 " + nick + " = " + channel + " :" + users + "\r\n"
#define RPL_ENDOFNAMES(nick, channel)                   ": 366 " + nick + " " + channel + " :End of /NAMES list\r\n"
#define ERR_NOSUCHNICK(nick)                            ": 401 " + nick + " :No such nick\r\n"

/* -------------------- CHANNEL ERROR MESSAGES -------------------- */
#define ERR_BADCHANNELKEY(channelName)                  ": 475 " + channelName + " :Cannot join channel (+k)\r\n"
#define ERR_INVCHANNAME                                 "Invalid channel name, must be: #<channel name> <?key>\r\n"

/* -------------------- TOPIC ERROR MESSAGES -------------------- */
#define ERR_CHANOPRIVSNEEDED(channelName)               ": 482 " + channelName + " :You're not channel operator\r\n"

/* -------------------- MODE ERROR MESSAGES -------------------- */
#define ERR_UNKNOWNMODE(source, channel, mode)		    ": 472 " + source + " " +  channel + " :Unknown Mode " + mode + "\r\n"
#define ERR_NOCHANNELREGISTER(channelName, targetClient) targetClient + " is not registered in the channel " + channelName  + "\r\n"

/* -------------------- INVITE ERROR MESSAGES -------------------- */
#define RPL_INVITE(nick, ip, channel, target)           ":" + nick + "!" + nick + "@" + ip + " INVITE " + target + " " + channel + "\r\n"
#define ERR_INVITEONLYCHAN(channelName)                 ": 473 " + channelName + " :Cannot join channel (+i)\r\n"

/* -------------------- KICK ERROR MESSAGES -------------------- */
#define ERR_CHANOPKICK(target)                          ": 482 " + target + " :You cannot KICK yourself" + "\r\n"
#define RPL_KICK(nick, target, channel)                 ":" + nick + " KICK " + channel + " " + target + "\r\n"

/* -------------------- PRIVMSG ERROR MESSAGES -------------------- */
#define RPL_PRIVMSG(source, target, message)		    ":" + source + " PRIVMSG " + target + " :" + message + "\r\n"
#define ERR_CANNOTSENDTOSELF()                          ": 400 :Cannot send to self\r\n"

/* -------------------- TOPIC ERROR MESSAGES -------------------- */
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message + "\r\n"



#include "../Server/Server.hpp"


#endif