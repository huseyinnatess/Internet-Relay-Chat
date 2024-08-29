#ifndef ERROR_HPP
#define ERROR_HPP

/* -------------------- GENERAL ERROR MESSAGES -------------------- */
#define ERR_NEEDMOREPARAMS(command)			            ": 461 " + command + " :Not enough parameters" + "\r\n"              //MODE
#define ERR_NOSUCHCHANNEL(channelName)			        ": 403 " + channelName + " :No such channel" + "\r\n"

/* -------------------- PASS ERROR MESSAGES -------------------- */
#define ERR_PASSWDMISMATCH                              ":Password incorrect\r\n"

/* -------------------- USER ERROR MESSAGES -------------------- */
#define ERR_ALREADYREGISTRED                            ": 462 :You may not reregister\r\n"

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

/* -------------------- CHANNEL ERROR MESSAGES -------------------- */
#define ERR_BADCHANNELKEY(channelName)                  ": 475 " + channelName + " :Cannot join channel (+k)\r\n"
#define ERR_INVCHANNAME                                 ": 479 :Invalid channel name\r\n"

/* -------------------- TOPIC ERROR MESSAGES -------------------- */
#define ERR_CHANOPRIVSNEEDED(channelName)               ": 482 " + channelName + " :You're not channel operator\r\n"

/* -------------------- MODE ERROR MESSAGES -------------------- */

#include "../Print/Print.hpp"
#include <string>
#include <unistd.h> //-> for close()
#include "../Server/Server.hpp"


#endif